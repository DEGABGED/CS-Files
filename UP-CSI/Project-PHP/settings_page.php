  <html><!DOCTYPE html>
<html lang="en">
  <head>
    <title>EventViewer - Settings</title>
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="styles/bootstrap-3.3.5-dist/css/bootstrap.min.css">
    <!-- Optional theme -->
    <link rel="stylesheet" href="styles/bootstrap-3.3.5-dist/css/bootstrap-theme.min.css">
  </head>
  <body>
    <?php
        session_start(); /*normally index.php starts the session, but you cant
            get here via index*/
        if(!isset($_SESSION['user_id'])) header('Location: index.php');
        include 'scripts/logout.php'
    ?>
    <!-- logout.php just redirects to the index login page. No pdo required. -->
    <?php include 'scripts/pdo_connect.php' ?>
    <!-- pdo_connect.php connects to the database. This should be the first
          thing to do, and this should be the only time to do it.

          TODO: Add catcher for when pdo_connect fails, then redirect to an
          error page.-->
    <?php include 'scripts/functions.php' ?>
    <!-- functions.php stores all the functions to be used, like displayEvent,
          isGroupFollowed, etc. -->

    <?php include 'scripts/toggle_follow.php' ?>
    <!-- toggle_follow.php only gets used if group_follow or
          group_unfollow variables are set -->
    <div class="container-fluid">
      <div class="row" id="page_header">
          <p>Header</p>
      </div>
      <div class="row" id="page_middle">
        <div class="col-xs-5 col-sm-3 col-md-3 col-lg-2 sidebar" id="sidebar">
          <!-- Insert list of groups and group search bar here
                and make this div fixed left-->

          <?php include 'scripts/sidebar.php' ?>
          <!-- sidebar.php will determine which group events to display on the
                front page, as well as display links to load the events. -->
        </div>
        <div class="col-xs-7 col-sm-9 col-md-9 col-lg-10" id="page_body">
          <!-- Insert settings and stuff. Group adding, Auth managing and events
                adding will be handled here-->
          <h3>Settings</h3>

          <?php include 'settings_index.php' ?>
          <!-- display_settings.php will display forms to either add events,
                admin, or change account settings. This depends on the get
                variable. -->

          <?php include 'scripts/post_requests.php' ?>
          <!-- post_request.php handles post requests made after logging in. -->
        </div>
        <div id="page_footer">
          <p>Footer</p>
        </div>
      </div>
    </div>
    <!-- Latest compiled and minified JavaScript -->
    <script src="styles/bootstrap-3.3.5-dist/js/bootstrap.min.js"></script>
  </body>
</html>
