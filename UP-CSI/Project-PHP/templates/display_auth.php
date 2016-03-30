<div class="form" id="addauth_form">
    <h3><?php echo getGroupName($_GET['group_id']) ?></h3>
    <h4><?php echo $_GET['request'] == 3 ? 'Add' : 'Delete'?> Authorized User</h4>
    <form action="<?php $_SERVER['PHP_SELF'].'?request='.$_GET['request'].'&group_id='.$_GET['group_id'] ?>" method="post">
        Name of user:<br /><input type="text" name="authuser" id="username_id" required><br /><br />
        <input type="submit">
    </form>
</div>

<!--
In case things fuck up:
    echo '<div class="form" id="addauth_form">'
        . '<h4>Add Authorized User</h4>'
        . '<form action="'.$_SERVER['PHP_SELF'].'?request='.$_GET['request'].'&group_id='.$_GET['group_id'].'" method="post">'
        . 'Name of user:<br /><input type="text" name="authuser" id="username_id" required><br /><br />'
        . '<input type="submit">'
        . '</form>';
-->
