<!DOCTYPE html><html>
<head>
<script src="https://code.jquery.com/jquery-3.5.0.js"></script>
</head>

<body>
<div id='php'></div>
<script type='text/javascript'>
setInterval(function() {
    $('#php').load('test.php')
}, 5000);
</script>
</body>
</html>

