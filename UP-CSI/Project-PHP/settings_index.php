<?php
    if(isset($_GET['request']) && isset($_GET['group_id'])){
        if(isUserAuthorized($_SESSION['user_id'], $_GET['group_id']) >= $_GET['request']){
            if($_GET['request'] == 1){ //add event
                include 'templates/display_addevent.php';
            } else if($_GET['request'] == 3){ //add authorized user
                include 'templates/display_auth.php';
            } else if($_GET['request'] == 2){ //delete event
                include 'templates/display_delevent.php';
            } else if($_GET['request'] == 4){ //delete authorized user
                include 'templates/display_auth.php';
            } else {
                echo '<p>No such request. Try again.</p>';
            }
        } else {
            echo '<p>Sorry, you\'re unauthorized for the request.</p>';
        }
    } else {
        include 'templates/display_settings.php';
    }
?>
