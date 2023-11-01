sel_ = document.getElementsByClassName("selected")[0];
function avoid(r) {
  if (sel_ != null) {
    sel_.className = "";
  }
  sel_ = r;
  sel_.className = "selected";
  document.getElementById("content").innerHTML = sel_.innerHTML;
  console.log(sel_.innerHTML);
}