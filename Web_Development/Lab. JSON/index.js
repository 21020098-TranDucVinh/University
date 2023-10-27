document.addEventListener("DOMContentLoaded", function () {
    fetchData();
});

function fetchData() {
    document.getElementById("loadDataButton").addEventListener("click", loadData);

    // Fetch data from backend
    function loadData() {
        const backendURL = "https://jsonplaceholder.typicode.com/users?fbclid=IwAR3NdVQHMlGu6VdKjQBQJ22rM7boZUL4alyX1LMCcFGMNcwZF8-XRUpyWNE";

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
                headerCell.textContent = key;
            }
        }

        // Create table rows and cells for data
        for (const item of data) {
            const row = table.insertRow(-1);
            for (const key in item) {
                if (item.hasOwnProperty(key)) {
                    const cell = row.insertCell(-1);
                    if (typeof item[key] === "object") {
                        // If the property is an object, iterate over its properties and create a string
                        const addressObject = item[key];
                        const addressString = Object.keys(addressObject).map(subKey => `${subKey}: ${addressObject[subKey]}`).join(", ");
                        cell.textContent = addressString;
                    } else {
                        cell.textContent = item[key];
                    }
                }
            }
        }

        const dataContainer = document.getElementById("dataContainer");
        dataContainer.innerHTML = "";
        dataContainer.appendChild(table);
    }
}