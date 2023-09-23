package ie.app.donation10.views

import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.NumberPicker
import android.widget.ProgressBar
import android.widget.RadioGroup
import androidx.appcompat.app.AppCompatActivity
import ie.app.donation10.R


class Donate : AppCompatActivity() {
    private var donateButton: Button? = null
    private var paymentMethod: RadioGroup? = null
    private var progressBar: ProgressBar? = null
    private var amountPicker: NumberPicker? = null

    @Override
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_donate)

        donateButton = findViewById(R.id.donateButton) as? Button

        paymentMethod = findViewById(R.id.paymentMethod) as? RadioGroup
        progressBar = findViewById(R.id.progressBar) as? ProgressBar
        amountPicker = findViewById(R.id.amountPicker) as? NumberPicker

        amountPicker?.setMinValue(0)
        amountPicker?.setMaxValue(1000)
        progressBar?.setMax(10000)
    }

    fun donateButtonPressed(view: View) {
        val amount = amountPicker?.getValue()
        val radioId = paymentMethod?.getCheckedRadioButtonId()
        val method = if (radioId == R.id.PayPal) "PayPal" else "Direct"
        var totalDonated = 0
        totalDonated += amount!!
        progressBar?.setProgress(totalDonated)


        Log.v("Donate", "Donate Pressed! with amount " + amount + ", method: " + method)
        Log.v("Donate", "Total Donated so far: " + totalDonated)
    }
}

