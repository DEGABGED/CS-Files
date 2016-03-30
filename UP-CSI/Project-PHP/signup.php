<html>
  <head>
    <title>EventViewer - Signup</title>
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="styles/bootstrap-3.3.5-dist/css/bootstrap.min.css">
    <!-- Optional theme -->
    <link rel="stylesheet" href="styles/bootstrap-3.3.5-dist/css/bootstrap-theme.min.css">
  </head>
  <body>
    <!-- ?php include 'login_credens.php' ? -->
    <div id="whole_page">
      <div id="page_header">

      </div>
      <div id="page_body">
        <div id="body_header">

        </div>
        <div class="form" id="login_form">
          <h3>Sign Up</h3>
          <form action="<?php echo $_SERVER["PHP_SELF"];?>" method="post">
            Username<br /><input type="text" name="username" id="username_id"><br /><br />
            Password<br /><input type="password" name="password" id="password_id"><br /><br />
            Reenter Password<br /><input type="password" name="password2" id="password2_id"><br /><br />
            <input type="submit">
          </form>
          <?php include 'scripts/signup_credens.php' ?>
        </div>
      </div>
      <div id="page_footer">

      </div>
    </div>
  </body>
</html>
