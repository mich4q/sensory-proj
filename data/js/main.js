$(function () {
    // Inicjalizacja danych czujników
    getSensorData();
    getThresholds();
    setInterval(getSensorData, 10000);

    // Obsługa zmiany trybu WiFi
    $("#wifiModeSwitch").change(function () {
        $('#ssid').val('');
        $('#password').val('');
    });

    // Obsługa przycisku zapisu ustawień sieci WiFi
    $('#save_network').click(function () {
        saveNetwork();
    });
    $('#send-data-file').click(function () {
        getDataFile();
    });

    // Obsługa ręcznego odświeżania danych czujników
    $('#getSensorData').click(function () {
        getSensorData();
    });

    // Obsługa zapisywania progów
    $('#save-thresholds').click(function () {
        const humidityThreshold = $('#humidity-threshold').val();
        const co2Threshold = $('#co2-threshold').val();

        if (humidityThreshold && co2Threshold) {
            if ( humidityThreshold > 100) {
               alert('Wilgotność nie może być większa niż 100%');
            }else if ( co2Threshold > 10000) {
              alert('CO2 nie może być większe niż 10000 ppm');
            }else if(humidityThreshold < 0 && co2Threshold < 0) {
                alert('Wartości nie mogą być ujemne');
            }else {
                saveThresholds(humidityThreshold, co2Threshold);
            }
        } else {
            alert('Please fill in all fields before saving.');
        }
    });
    // Obsługa ręcznego odświeżania danych czujników
    $('#pump-control').click(function () {
        pumpOn();
    });
    $('#fan-control').click(function () {
        fanOn();
    });
});
function pumpOn() {
    $.ajax({
        url: '/pumpControl',
        method: 'GET',
        success: function (response) {
            console.log('Pump turned on:', response);
        },
        error: function (xhr, status, error) {
            console.error('Error turning on pump:', error);
        }
    });
}
function fanOn() {
    $.ajax({
        url: '/fanControl',
        method: 'GET',
        success: function (response) {
            console.log('Fan turned on:', response);
        },
        error: function (xhr, status, error) {
            console.error('Error turning on fan:', error);
        }
    });
}

function getDataFile() {
    $.ajax({
        url: '/getDataFile',  // Endpoint na serwerze, który zwraca plik
        method: 'GET',
        success: function (response, status, xhr) {
            // Sprawdź status odpowiedzi
            if (xhr.status === 200) {
                console.log("Plik został poprawnie przesłany.");
                // alert("Plik został poprawnie przesłany.");
            } else {
                console.error("Błąd podczas przesyłania pliku. Status:", xhr.status);
                // alert("Błąd podczas przesyłania pliku.");
            }
        },
        error: function (xhr, status, error) {
            console.error('Błąd podczas komunikacji z serwerem:', error);
            // alert("Błąd podczas komunikacji z serwerem.");
        }
    });
}

// Funkcja do zapisu ustawień sieci WiFi
function saveNetwork() {
    const data = {
        ssid: $('#ssid').val(),
        password: $('#password').val(),
        wifiMode: $('input[name="mode"]:checked').val(),
    };

    $.ajax({
        url: '/savenetwork',
        type: 'GET',
        contentType: 'application/json',
        data: data,
        success: function (response) {
            console.log('Network settings saved:', response);
        },
        error: function (xhr, status, error) {
            console.error('Error saving network settings:', error);
        }
    });
}

// Funkcja do pobierania danych czujników
function getSensorData() {
    $.ajax({
        url: '/getData',
        method: 'GET',
        dataType: 'json',
        success: function (response) {
            if (response && typeof response === 'object') {
                $('#temp').text(response.temperature !== null ? response.temperature.toFixed(1) : 'No data');
                $('#hum').text(response.humidity !== null ? response.humidity.toFixed(1) : 'No data');
                $('#soil_hum').text(response.soil_humidity !== null ? response.soil_humidity.toFixed(1) : 'No data');
                $('#co2').text(response.CO2 !== null ? response.CO2 : 'No data');
                $('#timestamp').text(response.timestamp || 'No data');
            } else {
                displayError();
            }
        },
        error: function () {
            displayError();
        }
    });
}

// Funkcja do zapisywania progów
function saveThresholds(humidity, co2) {
    const data = {
        humidity: humidity,
        co2: co2,
    };

    $.ajax({
        url: '/saveThresholds',
        method: 'GET',
        contentType: 'application/json',
        data: data,
        success: function (response) {
            console.log('Thresholds saved:', response);
        },
        error: function (xhr, status, error) {
            console.error('Error saving thresholds:', error);
        }
    });
}

function getThresholds(){
    $.ajax({
        url: '/getThresholds',
        method: 'GET',
        dataType: 'json',
        success: function (response) {
            if (response && typeof response === 'object') {
                $('#humidity-threshold').val(response.soil_humidity);
                $('#co2-threshold').val(response.co2);
            } else {
                console.log("Error getting thresholds");
            }
        }
    });
}

// Funkcja do obsługi błędów podczas pobierania danych czujników
function displayError() {
    $('#temp').text('Error');
    $('#hum').text('Error');
    $('#soil_hum').text('Error');
    $('#co2').text('Error');
    $('#timestamp').text('Error');
}
