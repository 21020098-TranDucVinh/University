sel_ = document.getElementsByClassName("selected")[0];
function avoid(r) {
  if (sel_ != null) {
    sel_.className = "";
  }
  sel_ = r;
  sel_.className = "selected";

  frm = document.getElementById("myframe");
  if (sel_.id == "m1") {
    frm.src = "https://vnexpress.net";
  } else if (sel_.id == "m2") {
    frm.src = "https://dantri.com.vn";
  } else if (sel_.id == "m3") {
    frm.src = "https://voanews.com";
  } else if (sel_.id == "m4") {
    frm.src = "https://zing.vn";
  }
}