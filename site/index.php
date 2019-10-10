<!DOCTYPE html>
<html>
  <head>
    <title>Управління</title>
    <script type="text/javascript" src="js/jquery.js"></script>
    <link rel = "stylesheet" href = "index.css">
    <script src="cp/js/colpick.js" type="text/javascript"></script>
    <link rel="stylesheet" href="cp/css/colpick.css" type="text/css"/>
  </head>
  <body>
    <div class = "line ln1">
      <div class = "D1 diode" onclick="d_id = 1;" id = "1"></div>
      <div class = "D2 diode" onclick="d_id = 2;" id = "2"></div>
      <div class = "D3 diode" onclick="d_id = 3;" id = "3"></div>
      <div class = "D4 diode" onclick="d_id = 4;" id = "4"></div>
      <div class = "D5 diode" onclick="d_id = 5;" id = "5"></div>
      <div class = "D6 diode" onclick="d_id = 6;" id = "6"></div>
      <div class = "D7 diode" onclick="d_id = 7;" id = "7"></div>
      <div class = "D8 diode" onclick="d_id = 8;" id = "8"></div>
    </div>
    <div class="line ln2">
      <div class = "DD1 diode " onclick="d_id = 9;" id = "9"></div>
      <div class = "DD2 diode " onclick="d_id = 10;" id = "10"></div>
      <div class = "DD3 diode " onclick="d_id = 11;" id = "11"></div>
      <div class = "DD4 diode " onclick="d_id = 12;" id = "12"></div>
      <div class = "DD5 diode " onclick="d_id = 13;" id = "13"></div>
      <div class = "DD6 diode " onclick="d_id = 14;" id = "14"></div>
      <div class = "DD7 diode " onclick="d_id = 15;" id = "15"></div>
      <div class = "DD8 diode " onclick="d_id = 16;" id = "16"></div>
    </div>
    <script>
      var d_id = 0;

      $('.diode').colpick({
        onSubmit:function(hsb,hex,rgb,el,bySetColor) {
          element = document.getElementById(d_id);
          element.style.background = '#'+hex;
          $(el).colpickHide();
        }
      });

    </script>
  </body>

</html>
