var rows = document.getElementsByClassName("row");

for (let i = 0; i < rows.length; i++)
  rows[i].onclick = function () {
    let chk = this.getElementsByClassName("check")[0];
    if (chk.checked) {
      this.classList.remove("selected");
      document.getElementById("checkAll").checked = false;
      let c = document.getElementsByClassName("check");
      let j = 0;
      for (; j < c.length; j++)
        if (c[j].checked) break;
      if (j == c.length) document.querySelector("div.group-op").classList.add("nodisplay");
      else document.querySelector("div.group-op").classList.remove("nodisplay");

      chk.checked = false;
    } else {
      this.classList.add("selected");
      let c = document.getElementsByClassName("check");
      let j = 0;
      for (; j < c.length; j++)
        if (!c[j].checked) break;
      if (j == c.length) document.getElementById("checkAll").checked = true;
      else document.getElementById("checkAll").checked = false;
      document.querySelector("div.group-op").classList.remove("nodisplay");

      chk.checked = true;
    }
  };

document.getElementById("checkAll").onchange = function () {
  let c = document.getElementsByClassName("check");
  for (let i = 0; i < c.length; i++) {
    c[i].checked = this.checked;
    if (c[i].checked) c[i].parentNode.parentNode.classList.add("selected");
    else c[i].parentNode.parentNode.classList.remove("selected");
  }
  if (this.checked) document.querySelector("div.group-op").classList.remove("nodisplay");
  else document.querySelector("div.group-op").classList.add("nodisplay");
};

document.querySelector(".group-op-delete").onclick = function () {
  let c = document.getElementsByClassName("check");
  for (let i = c.length - 1; i >= 0; i--)
    if (c[i].checked) {
      c[i].parentNode.parentNode.parentNode.removeChild(c[i].parentNode.parentNode);
    }
};

var tbl = document.getElementById("tbl");

preProcessSortableTbl(tbl);

function preProcessSortableTbl(tbl) {
  // Do chÆ°a biáº¿t trÆ°á»›c sá»‘ báº£ng sáº¯p xáº¿p Ä‘Æ°á»£c
  // nĂªn khĂ´ng thá»ƒ dĂ¹ng cĂ¡c biáº¿n toĂ n cá»¥c Ä‘á»ƒ
  // biá»ƒu thá»‹ cá»™t vĂ  chiá»u Ä‘ang Ä‘Æ°á»£c sáº¯p xáº¿p cho tá»«ng báº£ng
  // nhÆ° á»Ÿ vĂ­ dá»¥ Ä‘Æ¡n giáº£n.

  // Giáº£i phĂ¡p: ThĂªm vĂ o trÆ°á»›c má»—i báº£ng sáº¯p xáº¿p Ä‘Æ°á»£c 
  // 2 Ä‘á»‘i tÆ°á»£ng hidden Ä‘á»ƒ lÆ°u thĂ´ng tin
  // cá»™t vĂ  chiá»u Ä‘ang Ä‘Æ°á»£c sáº¯p xáº¿p trĂªn báº£ng.

  var col = document.createElement("input");
  var dir = document.createElement("input");
  col.type = "hidden";
  dir.type = "hidden";
  col.value = "-1";
  dir.value = "";
  tbl.parentNode.insertBefore(col, tbl);
  tbl.parentNode.insertBefore(dir, tbl);

  // Tiá»n xá»­ lĂ½ cĂ¡c Ă´ tiĂªu Ä‘á» cá»™t sáº¯p xáº¿p Ä‘Æ°á»£c
  var hcells = tbl.rows[0].cells;
  for (var i = 0; i < hcells.length; i++)
    if (hcells[i].classList.contains("sortcol")) { // lĂ  cá»™t sáº¯p xáº¿p Ä‘Æ°á»£c
      // ChĂ¨n Ä‘á»‘i tÆ°á»£ng <span class="arrow"></span> vĂ o cuá»‘i tiĂªu Ä‘á»
      // Ä‘á»ƒ biá»ƒu thá»‹ mÅ©i tĂªn chiá»u sáº¯p xáº¿p.
      hcells[i].innerHTML += '<span class="arrow"></span>';

      // Xá»­ lĂ½ sá»± kiá»‡n kĂ­ch chuá»™t trĂªn Ă´ tiĂªu Ä‘á»
      hcells[i].onclick = function () {
        // Cá»™t vĂ  chiá»u Ä‘ang Ä‘Æ°á»£c sáº¯p xáº¿p trĂªn báº£ng chá»©a Ă´ tiĂªu Ä‘á»
        var d = this.parentNode.parentNode.parentNode.previousSibling;
        var c = d.previousSibling;

        // Bá» biá»ƒu thá»‹ cá»™t Ä‘ang Ä‘Æ°á»£c sáº¯p xáº¿p (náº¿u cĂ³)
        var j;
        for (j = 0; j < this.parentNode.cells.length; j++) {
          this.parentNode.cells[j].classList.remove("asc");
          this.parentNode.cells[j].classList.remove("desc");
        }

        // Láº¥y chá»‰ má»¥c cá»§a Ă´ tiĂªu Ä‘á»
        // (cĂ³ thá»ƒ gá»™p vá»›i vĂ²ng for trĂªn cho tá»‘i Æ°u nhÆ°ng
        //  Ä‘Æ°á»£c tĂ¡c ra cho dá»… hiá»ƒu)
        for (j = 0; j < this.parentNode.cells.length; j++)
          if (this.parentNode.cells[j] == this) break;

        if (c.value == j.toString()) {
          // Cá»™t chá»©a Ă´ tiĂªu Ä‘á» Ä‘ang Ä‘Æ°á»£c sáº¯p xáº¿p, Ä‘áº£o chiá»u
          d.value = (d.value == "desc" ? "asc" : "desc");

        } else {
          // Máº·c Ä‘á»‹nh sáº¯p xáº¿p tÄƒng dáº§n
          c.value = j.toString();
          d.value = "asc";
        }

        // ThĂªm biá»ƒu thá»‹ cá»™t Ä‘Æ°á»£c sáº¯p xáº¿p
        this.classList.add(d.value);

        // Sáº¯p xáº¿p
        sortTbl(this.parentNode.parentNode.parentNode);
      };
    }
}

function sortTbl(tbl) {
  var dir = tbl.previousSibling.value;
  var col = parseInt(tbl.previousSibling.previousSibling.value);

  for (var i = 1; i < tbl.rows.length; i++)
    for (var j = i + 1; j < tbl.rows.length; j++)
      if ((dir == "asc" && tbl.rows[i].cells[col].innerHTML.toLowerCase() >
        tbl.rows[j].cells[col].innerHTML.toLowerCase()) ||
        (dir == "desc" && tbl.rows[i].cells[col].innerHTML.toLowerCase() <
          tbl.rows[j].cells[col].innerHTML.toLowerCase())) {
        //hoĂ¡n vá»‹
        for (var t = 1; t < tbl.rows[i].cells.length; t++) {
          tmp = tbl.rows[i].cells[t].innerHTML;
          tbl.rows[i].cells[t].innerHTML = tbl.rows[j].cells[t].innerHTML;
          tbl.rows[j].cells[t].innerHTML = tmp;
        }
      }
}