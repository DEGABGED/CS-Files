<div class="form" id="addevent_form">
    <h3><?php echo getGroupName($_GET['group_id']) ?></h3>
    <h4>Add Event</h4>
        <form action="<?php echo $_SERVER['PHP_SELF'].'?request='.$_GET['request'].'&group_id='.$_GET['group_id'] ?>" method="post">
            Event Name:<br />
            <input type="text" name="event_name" id="eventname_id" required><br /><br />
            Event Date and Time:<br />
            <input type="date" name="event_date" id="eventdate_id" required>
            <input type="time" name="event_time" id="eventdate_id" required><br /><br />
            Event Venue:<br />
            <input type="text" name="event_venue" id="eventvenue_id" required><br /><br />
            Event Description:<br />
            <textarea rows="5" cols = "50" name="event_desc" id="eventdesc_id"></textarea><br /><br />
            <input type="submit">
        </form>
</div>

<!--
in case things don't work out:
    echo '<div class="form" id="addevent_form">'
        . '<h4>Add Event</h4>'
        . '<form action="'.$_SERVER['PHP_SELF'].'?request='.$_GET['request'].'&group_id='.$_GET['group_id'].'" method="post">'
        . 'Event Name:<br />'
        . '<input type="text" name="event_name" id="eventname_id" required><br /><br />'
        . 'Event Date and Time:<br />'
        . '<input type="date" name="event_date" id="eventdate_id" required>'
        . '<input type="time" name="event_time" id="eventdate_id" required><br /><br />'
        . 'Event Venue:<br />'
        . '<input type="text" name="event_venue" id="eventvenue_id" required><br /><br />'
        . 'Event Description:<br />'
        . '<textarea rows="5" cols = "50" name="event_desc" id="eventdesc_id"></textarea><br /><br />'
        . '<input type="submit">'
        . '</form>';
-->
