package org.inspace.port;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.DocumentsContract;
import android.provider.DocumentsContract.Document;
import android.view.Gravity;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Start: the game when its files are in the game folder (the app's external files folder, which
 * the port's platform_data_dir() names), else a page that names that folder and can copy the
 * user's own game folder into it (the system's folder picker).
 */
public class SetupActivity extends Activity {
    private static final int PICK_FOLDER = 1;

    private TextView message;
    private Button importButton;
    private Button startButton;

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);
        if (haveGame()) {
            startGame();
            return;
        }
        message = new TextView(this);
        message.setTextSize(18);
        message.setTextIsSelectable(true);
        importButton = new Button(this);
        importButton.setText(R.string.setup_import);
        importButton.setOnClickListener(v -> startActivityForResult(
                new Intent(Intent.ACTION_OPEN_DOCUMENT_TREE), PICK_FOLDER));
        startButton = new Button(this);
        startButton.setText(R.string.setup_retry);
        startButton.setOnClickListener(v -> {
            if (haveGame()) {
                startGame();
            } else {
                showMissing();
            }
        });
        LinearLayout page = new LinearLayout(this);
        page.setOrientation(LinearLayout.VERTICAL);
        page.setGravity(Gravity.CENTER_HORIZONTAL);
        int pad = (int) (24 * getResources().getDisplayMetrics().density);
        page.setPadding(pad, pad, pad, pad);
        page.addView(message);
        page.addView(importButton);
        page.addView(startButton);
        ScrollView scroll = new ScrollView(this);
        scroll.addView(page);
        setContentView(scroll);
        showMissing();
    }

    private File gameFolder() {
        return getExternalFilesDir(null);
    }

    private boolean haveGame() {
        File dir = gameFolder();
        String[] names = dir != null ? dir.list() : null;
        if (names != null) {
            for (String name : names) {
                if (name.equalsIgnoreCase("INSPACE.EXE")) {
                    return true;
                }
            }
        }
        return false;
    }

    private void startGame() {
        startActivity(new Intent(this, GameActivity.class));
        finish();
    }

    private void showMissing() {
        File dir = gameFolder();
        message.setText(getString(R.string.setup_missing, dir != null ? dir.getPath() : "?"));
    }

    @Override
    protected void onActivityResult(int request, int result, Intent data) {
        super.onActivityResult(request, result, data);
        if (request != PICK_FOLDER || result != RESULT_OK || data == null || data.getData() == null) {
            return;
        }
        Uri tree = data.getData();
        importButton.setEnabled(false);
        startButton.setEnabled(false);
        new Thread(() -> {
            String error = null;
            try {
                copyTree(tree, DocumentsContract.getTreeDocumentId(tree), gameFolder());
            } catch (IOException | RuntimeException e) {
                error = e.getMessage();
            }
            String failed = error;
            runOnUiThread(() -> {
                importButton.setEnabled(true);
                startButton.setEnabled(true);
                if (failed != null) {
                    message.setText(getString(R.string.setup_failed, failed));
                } else if (haveGame()) {
                    startGame();
                } else {
                    showMissing();
                }
            });
        }, "import").start();
    }

    /** Copies the document folder id of tree, with its subfolders, into dir. */
    private void copyTree(Uri tree, String id, File dir) throws IOException {
        ContentResolver resolver = getContentResolver();
        Uri children = DocumentsContract.buildChildDocumentsUriUsingTree(tree, id);
        String[] columns = {Document.COLUMN_DOCUMENT_ID, Document.COLUMN_DISPLAY_NAME, Document.COLUMN_MIME_TYPE};
        if (!dir.isDirectory() && !dir.mkdirs()) {
            throw new IOException("cannot make " + dir);
        }
        try (Cursor c = resolver.query(children, columns, null, null, null)) {
            if (c == null) {
                throw new IOException("cannot read the folder");
            }
            while (c.moveToNext()) {
                String child = c.getString(0);
                File target = new File(dir, new File(c.getString(1)).getName());
                if (Document.MIME_TYPE_DIR.equals(c.getString(2))) {
                    copyTree(tree, child, target);
                } else {
                    copyFile(resolver, DocumentsContract.buildDocumentUriUsingTree(tree, child), target);
                }
            }
        }
    }

    private void copyFile(ContentResolver resolver, Uri from, File to) throws IOException {
        runOnUiThread(() -> message.setText(getString(R.string.setup_copying, to.getName())));
        try (InputStream in = resolver.openInputStream(from); OutputStream out = new FileOutputStream(to)) {
            if (in == null) {
                throw new IOException("cannot read " + to.getName());
            }
            byte[] buf = new byte[65536];
            for (int n; (n = in.read(buf)) > 0; ) {
                out.write(buf, 0, n);
            }
        }
    }
}
