# jt.py SEG:OFF : disassembly with jump tables decoded and xrefs on targets
import sys,re,io,contextlib
sys.path.insert(0,'/home/user/opinnerspacedecomp/tools')
import disfn, capstone
sym=disfn.Symbols('/home/user/opinnerspacedecomp/unpacked/INSPACE.EXE')
sn,off=sys.argv[1].split(':'); sn=int(sn); off=int(off,16)
size=sym.inv[(sn,off)][0]; body=sym.body(sn); end=off+size
md=capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_16)
tables={}  # start->(n)
lines=[]; xref={}
a=off; lastcmp=None
while a<end:
    if a in tables:
        n=tables[a]
        ents=[int.from_bytes(body[a+2*i:a+2*i+2],'little') for i in range(n)]
        lines.append((a,'  %04x  TABLE %s'%(a,' '.join('%d:%04x'%(i,e) for i,e in enumerate(ents)))))
        for i,e in enumerate(ents): xref.setdefault(e,[]).append('T%04x[%d]'%(a,i))
        a+=2*n; continue
    it=next(md.disasm(body[a:end],a))
    t='%s %s'%(it.mnemonic,it.op_str)
    m=re.match(r'cmp ax, (0x[0-9a-f]+|\d+)$',t)
    if m: lastcmp=int(m.group(1),0)
    m=re.match(r'jmp word ptr cs:\[bx \+ (0x[0-9a-f]+)\]',t)
    if m: tables[int(m.group(1),16)]=lastcmp+1
    if it.mnemonic.startswith('j') and it.op_str.startswith('0x'):
        xref.setdefault(int(it.op_str,16),[]).append('%04x'%a)
    lines.append((a,None))
    a+=it.size
# now print via disfn for each non-table line
buf=io.StringIO()
with contextlib.redirect_stdout(buf): disfn.disasm(sym,sn,off)
dl={}
for l in buf.getvalue().splitlines()[1:]:
    m=re.match(r'  ([0-9a-f]{4})  ',l)
    if m: dl[int(m.group(1),16)]=l
for a,l in lines:
    if a in xref: print('L%04x:   <- %s'%(a,' '.join(xref[a])))
    if l: print(l)
    else:
        if a in dl: print(dl[a])
        else:
            it=next(md.disasm(body[a:end],a)); print('  %04x  %-14s %s %s'%(a,it.bytes.hex(),it.mnemonic,it.op_str))
