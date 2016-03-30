<!DOCTYPE html>
<html lang="en">
  <head>
    <title>EventViewer - Login</title>
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" integrity="sha512-dTfge/zgoMYpP7QbHy4gWMEGsbsdZeCXz7irItjcC3sPUFtf0kuFbDz/ixG7ArTxmDjLXDmezHubeNikyKGVyQ==" crossorigin="anonymous">
    <!-- Optional theme -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css" integrity="sha384-aUGj/X2zp5rLCbBxumKTCw2Z50WgIr1vs/PFN4praOTvYXWlVyh2UtNUU0KAUhAX" crossorigin="anonymous">
  </head>
  <body>
    <?php include 'scripts/login_credens.php' ?>
    <div id="whole_page">
      <div id="page_header">

      </div>
      <div id="page_body">
        <div id="body_header">

        </div>
        <div class="form" id="login_form">
          <h3>Log In</h3>
          <form action="<?php echo $_SERVER["PHP_SELF"];?>" method="post">
            Username<br /><input type="text" name="username" id="username_id"><br /><br />
            Password<br /><input type="password" name="password" id="password_id"><br /><br />
            <input type="submit">
          </form>
        </div>
        <a href="signup.php"><button>Sign Up</button></a>
        <!-- ?php include 'login_credens.php' ? -->
      </div>
      <div id="page_footer">

      </div>
    </div>
    <!-- Latest compiled and minified JavaScript -->
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js" integrity="sha512-K1qjQ+NcF2TYO/eI3M6v8EiNYZfA95pQumfvcVrTHtwQVDG+aHRqLi/ETn2uB+1JqwYqVG3LIvdm9lj6imS/pQ==" crossorigin="anonymous"></script>
  </body>
</html>
