import QtQuick 2.0

Item {
    id: helper_item

    function is_this_file_a_pdf(file_url) {
        return file_url.includes(".pdf");
    }

    function open_command_for_this_pdf(file_url) {
        var file_path = decodeURIComponent(file_url.replace(/^(file:\/{2})/, "")).split(".pdf#")[0] + ".pdf";
        var page = file_url.split(".pdf#")[1].split(";")[0];
        var command = "okular \"" + file_path + "\" -p " + page;
        return command;
    }

    function openURL(url) {
        var url = bookmarklist.currentItem.tooltip;
        if (helper.is_this_file_a_pdf(url)) {
            var command = helper.open_command_for_this_pdf(url);
            executable.exec(command);
        } else {
            Qt.openUrlExternally(url);
        }
    }

}
