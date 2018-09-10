package tft.lcd.root.tftlcd;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import java.util.UUID;

public class MainActivity extends AppCompatActivity {
    StringBuilder sb = new StringBuilder();
    Blue b;
    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        b = new Blue();
        b.connect();
    }

    public void send(View v) {
        b.write("drawCircle,20,10,30,1/");
    }
}
