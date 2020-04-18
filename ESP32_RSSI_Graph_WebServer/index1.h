const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>

<head>
  <title>Line Chart | Circuits4you.com</title>
  <!--For offline ESP graphs see this tutorial https://circuits4you.com/2018/03/10/esp8266-jquery-and-ajax-web-server/ -->
  <script src = "https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>  
  <style>
  canvas{
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }

  /* Data Table Styling */
  #dataTable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
  }

  #dataTable td, #dataTable th {
    border: 1px solid #ddd;
    padding: 8px;
  }

  #dataTable tr:nth-child(even){background-color: #f2f2f2;}

  #dataTable tr:hover {background-color: #ddd;}

  #dataTable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #4CAF50;
    color: white;
  }
  button{
    margin: 20px;
    padding: 10px 30px;
  }
  </style>
</head>

<body>
    <div style="text-align:center;"><b>RSSI (dBm) </b><br>Real Time RSSI Data Logging with Graphs using ESP32</div>
    <div class="chart-container" position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>
<div>
  <button id="download">Download CSV File</button>
  <table id="dataTable">
    <tr>
      <th>Time</th>
      <th>RSSI_AP1 (dBm)</th>
      <th>RSSI_AP2 (dBm)</th>
      <th>RSSI_AP3 (dBm)</th>
    </tr>
  </table>
</div>
<br>
<br>  

<script>
//Graphs visit: https://www.chartjs.org
var values = [];
var timeStamp = [];
function showGraph()
{

    var ctx = document.getElementById("Chart").getContext('2d');
    var Chart2 = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timeStamp,  //Bottom Labeling
            datasets: [
              {
                label: "RSSI_AP1 (dBm)",
                fill: false,  //Try with true
                backgroundColor: 'rgba(238, 17, 17, 1)', //Dot marker color
                borderColor: 'rgba(238, 17, 17, 1)', //Graph Line Color
                data: values.map(item => item[0]) || [],
              },
              {
                label: "RSSI_AP2 (dBm)",
                fill: false,  //Try with true
                backgroundColor: 'rgba(24, 17, 238, 1)', //Dot marker color
                borderColor: 'rgba(24, 17, 238, 1)', //Graph Line Color
                data: values.map(item => item[1]) || [],
              },
              {
                label: "RSSI_AP3 (dBm)",
                fill: false,  //Try with true
                backgroundColor: 'rgba(17, 151, 26, 1)', //Dot marker color
                borderColor: 'rgba(17, 151, 26, 1)', //Graph Line Color
                data: values.map(item => item[2]) || [],
              },
            ],
        },
        options: {
            title: {
                    display: true,
                    text: "RSSI (dBm)"
                },
            maintainAspectRatio: false,
            elements: {
            line: {
                    tension: 0.5 //Smoothening (Curved) of data lines
                }
            },
            scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero:true
                        }
                    }]
            }
        }
    });

}

//On Page load show graphs
window.onload = function() {
  showGraph();
};

//Ajax script to get ADC voltage at every 5 Seconds 
//Read This tutorial https://circuits4you.com/2018/02/04/esp8266-ajax-update-part-of-web-page-without-refreshing/

setInterval(function() {
  // Call a function repetatively with 5 Second interval
  getData();
}, 5000); //5000mSeconds update rate
 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     //Push the data in array
  var time = new Date().toLocaleTimeString();
  var ADCValue = this.responseText; 
      ADCValue = ADCValue.split(";")
      values.push(ADCValue);
      timeStamp.push(time);
      showGraph();  //Update Graphs
  //Update Data Table
    var table = document.getElementById("dataTable");
    var row = table.insertRow(1); //Add after headings
    var cell1 = row.insertCell(0);
    cell1.innerHTML = time;
    ADCValue.map((power, index) => {
      let cell = row.insertCell(index + 1)
      cell.innerHTML = power
    })
  }
  };
  xhttp.open("GET", "readADC", true); //Handle readADC server on ESP8266
  xhttp.send();
}
    
// csv export
const download = ()=>{
  const filename = `raw_data_${new Date().getTime()}.csv`
  let table = document
    .getElementById('dataTable')
    .querySelectorAll("th")

  let text = ""
  
  table.forEach(header => {
    text += `"${header.innerText}",`
  });

  text += "\n" + values.map((item, index) => `${timeStamp[index]},${item.join(",")}`)
    .join("\n")
  let uri = "data:text/csv;charset=utf-8," + encodeURI(text)
  
  let a = document.createElement('a')
  a.setAttribute('download', filename)
  a.setAttribute('href', uri)
  a.setAttribute('target', '_blank')
  a.click()
  a.remove()
  
}

document
  .getElementById('download')
  .addEventListener('click', download)

</script>
</body>

</html>
)=====";