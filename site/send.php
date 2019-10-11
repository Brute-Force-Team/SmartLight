<?php
  if(isset($_POST['params'])){
    $param = $_POST['params'];
    file_get_contents("192.168.43.250/?text=$param");
  }
?>
