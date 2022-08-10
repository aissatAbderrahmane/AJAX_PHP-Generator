<?php
/**
 * @package learning
 */

 use DBZ\test;
require "vendor/autoload.php";

$t = new test();
$t->printer();

?>

<!DOCTYPE html>
<html>
<head>
<script src="jquery.js" integrity="sha256-QWo7LDvxbWT2tbbQ97B53yJnYU3WhH/C8ycbRAkjPDc=" crossorigin="anonymous"></script>

</head>

<body class="bg-gradient-primary">
<form id="posting" method="post" >
<input type="text" id="name" name="nom" />
<input type="text" id="surname" name="surname" />
<input type="button"  id="click" name="submit" value="send" />
</form>
<div id="hello">
</div>
<script>
$("#click").on('click',function (){
    name = $("#name").val();
    surnome = $("#surname").val();
     jval = {
        'nom' : name,
        'surname' : surnome    
    };
    $.ajax({
        url : "verify.php",
        method : "post",
        dataType: "JSON",
        data : jval,
        success: function(dd){
            alert(dd);
        }
    });
});    


</script>
