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
      <div class = "D1 diode" onclick="d_id = 1;" id = "9"></div>
      <div class = "D2 diode" onclick="d_id = 2;" id = "10"></div>
      <div class = "D3 diode" onclick="d_id = 3;" id = "11"></div>
      <div class = "D4 diode" onclick="d_id = 4;" id = "12"></div>
      <div class = "D5 diode" onclick="d_id = 5;" id = "13"></div>
      <div class = "D6 diode" onclick="d_id = 6;" id = "14"></div>
      <div class = "D7 diode" onclick="d_id = 7;" id = "15"></div>
      <div class = "D8 diode" onclick="d_id = 8;" id = "16"></div>
    </div>
    <div class="buttons">
      <div class = "btn" onclick="sendtext('Y')">
        Ввімкнути/вимкнути
      </div>
      <div class= "btn" onclick="sendtext('A')">
        Автоматичний режим
      </div>
      <div class="btn" onclick="sendtext('D')">
        Увімкнути датчики
      </div>
    </div>
    <script>
      var d_id = 0;
      var on = false;


      $('.diode').colpick({
        onSubmit:function(hsb,hex,rgb,el,bySetColor) {
          var Class = "D"+d_id;
          elements = document.getElementsByClassName(Class);
          var red = rgb.r;
          var green = rgb.g;
          var blue = rgb.b;
          if(red == 0){ red = 1;}
          if(green == 0){ green = 1;}
          if(blue == 0){ blue = 1;}
          elements[0].style.background = '#'+hex;
          elements[1].style.background = '#'+hex;
          var id = d_id + 60;

          var ob = {
            'red' : red,
            'green' : green,
            'blue' : blue,
            'id' : id
          };

          $.ajax({
            type:'POST',
            url:'write.php',
            dataType:'json',
            data:"param="+JSON.stringify(ob),
            success:function(html) {
            }
          });

          $(el).colpickHide();
        }
      });
      function sendtext(text){
        if(text == 'Y'){
          if(on == false){
            on = true;
            text='Y';
          }else{
            on=true;
            text='N';
          }
        }

        $.ajax({
          type:'POST',
          url:'send.php',
          dataType:'text',
          data:"param="+text,
          success:function(html) {
          }
        });
      }

    </script>
  </body>

</html>
