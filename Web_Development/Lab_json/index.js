document.addEventListener("DOMContentLoaded", function () {
    fetchData();
});

function fetchData() {
    document.getElementById("loadDataButton").addEventListener("click", loadData);

    // Fetch data from backend
    function loadData() {
        const backendURL = "/data.json";

        const xhr = new XMLHttpRequest();

        xhr.open("GET", backendURL, true);

        xhr.onload = function () {
            if (xhr.status >= 200 && xhr.status < 300) {
                const data = JSON.parse(xhr.responseText);
                console.log('Request succeeded with JSON response', data);
                createTable(data);
            } else {
                console.log('Request failed', xhr.statusText);
            }
        };

        xhr.send();
    }

    // Display data into a table
    function createTable(data) {
        const table = document.createElement("table");

        // Create the table header
        const headerRow = table.insertRow(0);
        for (const key in data[0]) {
            if (data[0].hasOwnProperty(key)) {
                const headerCell = headerRow.insertCell(-1);
                headerCell.textContent = key.toUpperCase();
                // add style to header cell
                headerCell.style.fontWeight = "bold";
            }
        }

        // Create table rows and cells for data
        for (const item of data) {
            var r = document.createElement("tr");
            var c1 = document.createElement("td");
            var c2 = document.createElement("td");
            var c3 = document.createElement("td");
            c1.innerHTML = item.name;
            c2.innerHTML = item.age;
            c3.innerHTML = item.cars.length;
            for (var j = 0; j < item.cars.length; j++)
                c3.innerHTML += "<br>" + item.cars[j].name + " - " + item.cars[j].models;
            r.appendChild(c1);
            r.appendChild(c2);
            r.appendChild(c3);
            table.appendChild(r);
        }

        const dataContainer = document.getElementById("dataContainer");
        dataContainer.innerHTML = "";
        dataContainer.appendChild(table);
    }
}