package com.loo.looengine;


import android.app.AlertDialog;
import android.app.NativeActivity;
import android.content.DialogInterface;
import android.content.pm.ApplicationInfo;
import android.os.Bundle;

import java.util.concurrent.Semaphore;

public class LooEngineActivity extends NativeActivity {

    static {
        // Load native library
        //System.loadLibrary("testframework" + BuildConfig.LIB_NAME_POSTFIX);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    // Use a semaphore to create a modal dialog

    private final Semaphore semaphore = new Semaphore(0, true);

    public void showAlert(final String message)
    {
        final LooEngineActivity activity = this;

        ApplicationInfo applicationInfo = activity.getApplicationInfo();
        final String applicationName = applicationInfo.nonLocalizedLabel.toString();

        this.runOnUiThread(new Runnable() {
            public void run() {
                AlertDialog.Builder builder = new AlertDialog.Builder(activity, android.R.style.Theme_Material_Dialog_Alert);
                builder.setTitle(applicationName);
                builder.setMessage(message);
                builder.setPositiveButton("Close", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        semaphore.release();
                    }
                });
                builder.setCancelable(false);
                AlertDialog dialog = builder.create();
                dialog.show();
            }
        });
        try {
            semaphore.acquire();
        }
        catch (InterruptedException e) { }
    }
}
