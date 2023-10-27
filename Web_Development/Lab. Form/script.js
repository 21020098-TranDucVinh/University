document.getElementById("name").focus();

document.getElementById("name").onblur = function () {
  this.value = ChuanhoaTen(this.value);
};

document.getElementById("name").onkeyup = function (e) {
  DoKeyup(e, this, 'address');
};

document.getElementById("address").onkeyup = function (e) {
  DoKeyup(e, this, 'birthday');
};

document.getElementById("birthday").onkeyup = function (e) {
  DoKeyup(e, this, 'email');
};

document.getElementById("email").onkeyup = function (e) {
  DoKeyup(e, this, 'fixed');
};

function DoKeyup(e, myself, nextcontrolid) {
  if (window.event) e = window.event; //de chay ca tren IE
  if (e.keyCode == 13) {
    document.getElementById(nextcontrolid).focus();
  }
}

function Chapnhan() {
  var okie = true; //chua co loi
  //xoa cac thong bao loi
  document.getElementById("name_error").innerHTML = "";
  document.getElementById("birthday_error").innerHTML = "";
  document.getElementById("email_error").innerHTML = "";
  document.getElementById("username_error").innerHTML = "";
  document.getElementById("pass_error").innerHTML = "";
  document.getElementById("repass_error").innerHTML = "";

  //kiem tra cac truong bat buoc nhap
  if (document.getElementById("pass").value == "") {
    document.getElementById("pass_error").innerHTML = "Quý vị chưa nhập mật khẩu";
    document.getElementById("pass").focus();
    okie = false;
  } else if (document.getElementById("repass").value == "") {
    document.getElementById("repass_error").innerHTML = "Quý vị chưa gõ lại mật khẩu";
    document.getElementById("repass").focus();
    okie = false;
  } else if (document.getElementById("pass").value != document.getElementById("repass").value) {
    document.getElementById("pass_error").innerHTML = "Mật khẩu và gõ lại mật khẩu không trùng nhau";
    document.getElementById("pass").focus();
    okie = false;
  }

  if (document.getElementById("username").value == "") {
    document.getElementById("username_error").innerHTML = "Quý vị chưa nhập tên sử dụng";
    document.getElementById("username").focus();
    okie = false;
  } else if (!laTenSD(document.getElementById("username").value)) {
    document.getElementById("username_error").innerHTML = "Tên sử dụng không đúng định dạng";
    document.getElementById("username").focus();
    okie = false;
  }

  if (document.getElementById("email").value == "") {
    document.getElementById("email_error").innerHTML = "Quý vị chưa nhập e-mail";
    document.getElementById("email").focus();
    okie = false;
  } else if (!laEmail(document.getElementById("email").value)) {
    document.getElementById("email_error").innerHTML = "E-mail không đúng định dạng";
    document.getElementById("email").focus();
    okie = false;
  }

  if (document.getElementById("birthday").value == "") {
    document.getElementById("birthday_error").innerHTML = "Quý vị chưa nhập ngày sinh";
    document.getElementById("birthday").focus();
    okie = false;
  } else if (!laNgayThang(document.getElementById("birthday").value)) {
    document.getElementById("birthday_error").innerHTML = "Ngày sinh không đúng định dạng";
    document.getElementById("birthday").focus();
    okie = false;
  }


  if (document.getElementById("name").value == "") {
    document.getElementById("name_error").innerHTML = "Quý vị chưa nhập họ tên";
    document.getElementById("name").focus();
    okie = false;
  }

  //neu tất cả các dữ liệu được nhập đúng đắn
  //submit form
  if (okie) document.getElementById("form1").submit();
}

//kiem tra s la email hay khong
function laEmail(s) {
  email = s.split('@');
  if (email.length != 2) return false;
  smurf = email[1].split('.');
  if (smurf.length < 2) return false;
  for (let i = 0; i < smurf.length; i++) {
    if (smurf[i].length == 0) return false;
  }
  return true;
}

//kiem tra s la ten su dung hop le hay khong
function laTenSD(s) {
  user = s.split(' ');
  if (user.length != 1) return false;
  return true;
}

function laNgayThang(d) { //d = nn/tt/nnnn
  //kiem tra d co phai la ngay thang

  //tach xau d boi dau /
  s = d.split('/');

  if (s.length != 3) return false; //phai co 3 phan
  if (isNaN(s[0]) || isNaN(s[1]) || isNaN(s[2])) return false;//ca 3 la so

  //chuyen thanh cac so nguyen
  ngay = parseInt(s[0]);
  thang = parseInt(s[1]);
  nam = parseInt(s[2]);

  //kiem tra
  if (thang > 12 || thang < 1) return false;
  if (thang == 1 || thang == 3 || thang == 5 || thang == 7 || thang == 8 || thang == 10 || thang == 12) {
    if (ngay > 31) return false;
  } else if (thang == 2) {
    if (nam % 4 == 0 && nam % 100 != 0) {
      if (ngay > 29) return false;
    } else if (ngay > 28) return false;
  } else if (ngay > 30) return false;

  if (ngay < 1) return false;

  date = new Date();
  if (nam > date.getFullYear() || nam < 1950) return false;

  return true;
}


//chuan hoa ten
function ChuanhoaTen(ten) {
  dname = ten;
  ss = dname.split(' ');
  dname = "";
  for (i = 0; i < ss.length; i++)
    if (ss[i].length > 0) {
      if (dname.length > 0) dname = dname + " ";
      dname = dname + ss[i].substring(0, 1).toUpperCase();
      dname = dname + ss[i].substring(1).toLowerCase();
    }
  return dname;
}

//bam nut bo qua
function Boqua() {
  document.location.href = "../";
}

// hien thi anh chan dung
document.getElementById("FileUpload1").onchange = function () {
  let preview = document.querySelector("img.preview");
  let file = this.files[0];
  let reader = new FileReader();
  reader.onload = function () {
    preview.src = reader.result;
  };
  if (file) {
    reader.readAsDataURL(file);
    preview.classList.remove("nodisplay");
  }
}

document.getElementById("birthday").addEventListener("input", function () {
  let dateInput = this.value;
  dateInput = dateInput.replace(/\D/g, "");
  if (dateInput.length > 8) {
    dateInput = dateInput.substring(0, 8);
  }
  if (dateInput.length > 2 && dateInput.length <= 4) {
    dateInput = dateInput.substring(0, 2) + "/" + dateInput.substring(2);
    console.log(dateInput.length + " =1=  " + dateInput);
  } else if (dateInput.length > 4) {
    dateInput = dateInput.substring(0, 2) + "/" + dateInput.substring(2, 4) + "/" + dateInput.substring(4);
    console.log(dateInput.length + " =2=  " + dateInput);
  }
  this.value = dateInput;
});