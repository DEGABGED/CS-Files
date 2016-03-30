<!DOCTYPE html>
<html lang="en">
  <head>
    <title>EventViewer - Home</title>
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="styles/bootstrap-3.3.5-dist/css/bootstrap.min.css">
    <!-- Optional theme -->
    <link rel="stylesheet" href="styles/bootstrap-3.3.5-dist/css/bootstrap-theme.min.css">
  </head>
  <body>
    <?php include 'scripts/logout.php' ?>
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
                <!-- Insert group events, and in-page forms -->
                <?php include 'scripts/display_events.php' ?>
                <!-- display_events.php takes a get query (search, group_follow,
                    group_unfollow, etc.).

                    Possible queries: search, group_follow, group_unfollow-->
                <?php include 'scripts/search_bar.php' ?>
                <!-- search_bar.php will show search RESULTS (TODO) upon search query -->
            </div>
        </div>
        <div id="page_footer">
            <p>Footer</p>
        </div>
    </div>
    <!-- Latest compiled and minified JavaScript -->
    <script src="styles/bootstrap-3.3.5-dist/js/bootstrap.min.js"></script>
  </body>
</html>
