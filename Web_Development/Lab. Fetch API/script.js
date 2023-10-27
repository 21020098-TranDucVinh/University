document.getElementById("getUser").addEventListener("click", getUserById);

function getUserById() {
  var userId = document.getElementById("userId").value;

  // check null
  if (userId == "") {
    alert("Please enter user ID");
    return;
  }

  // Tạo URL API dựa trên user ID
  var apiUrl = `https://jsonplaceholder.typicode.com/users/${userId}`;

  // Tạo yêu cầu GET đến API
  var xhr = new XMLHttpRequest();
  xhr.open("GET", apiUrl, true);

  // Xử lý sự kiện khi nhận được phản hồi từ API
  xhr.onload = function () {
    if (xhr.status === 200) {
      // Phân tích dữ liệu JSON từ phản hồi của API
      var user = JSON.parse(xhr.responseText);

      // Hiển thị dữ liệu trả về
      var userDetailsDiv = document.getElementById("userDetails");
      userDetailsDiv.innerHTML = "";
      var box = document.createElement("div");
      box.className = "col";
      box.innerHTML = `
            <p><strong>Name:</strong> ${user.name}</p>
            <p><strong>Email:</strong> ${user.email}</p>
            <p><strong>Phone:</strong> ${user.phone}</p>
            <p><strong>Website:</strong> ${user.website}</p>
          `;
      userDetailsDiv.appendChild(box);
    }
  };
  // Gửi yêu cầu GET đến API
  xhr.send();
}

document.getElementById("getAllUsers").addEventListener("click", getAllUsers);

function getAllUsers() {
  var apiUrl = "https://jsonplaceholder.typicode.com/users";
  var xhr = new XMLHttpRequest();
  xhr.open("GET", apiUrl, true);
  xhr.onload = function () {
    if (xhr.status === 200) {
      var users = JSON.parse(xhr.responseText);
      var usersDiv = document.getElementById("allUsers");
      usersDiv.innerHTML = "";
      users.forEach(function (user) {
        var box = document.createElement("div");
        box.className = "col";
        box.innerHTML = `
              <h3>${user.name}</h3>
              <p><strong>Email:</strong> ${user.email}</p>
              <p><strong>Phone:</strong> ${user.phone}</p>
              <p><strong>Website:</strong> ${user.website}</p>
            `;
        usersDiv.appendChild(box);
      });
    } else {
      console.log("Error");
    }
  };

  xhr.send();
}

// Lắng nghe sự kiện click vào nút "Create Post"
document.getElementById("createPost").addEventListener("click", function () {
  // Lấy giá trị title và body từ các trường input
  var title = document.getElementById("title").value;
  var body = document.getElementById("body").value;

  // Kiểm tra dữ liệu nhập vào
  if (title == "" || body == "") {
    alert("Please enter title and body");
    return;
  }

  // Tạo URL API
  var apiUrl = "https://jsonplaceholder.typicode.com/posts";

  // Tạo yêu cầu POST đến API
  var xhr = new XMLHttpRequest();
  xhr.open("POST", apiUrl, true);
  xhr.setRequestHeader("Content-Type", "application/json");

  // Xử lý sự kiện khi nhận được phản hồi từ API
  xhr.onload = function () {
    if (xhr.status === 201) {
      // Phân tích dữ liệu JSON từ phản hồi của API
      var post = JSON.parse(xhr.responseText);

      // Hiển thị dữ liệu trả về
      var postDetailsDiv = document.getElementById("postDetails");
      postDetailsDiv.innerHTML = "";
      var box = document.createElement("div");
      box.innerHTML = `
        <p><strong>Title:</strong> ${post.title}</p>
        <p><strong>Body:<strong> ${post.body}</p>
      `;

      postDetailsDiv.appendChild(box);
    }
  };

  // Gửi yêu cầu POST đến API với body là nội dung đã nhập
  var data = JSON.stringify({ title: title, body: body });
  xhr.send(data);
});