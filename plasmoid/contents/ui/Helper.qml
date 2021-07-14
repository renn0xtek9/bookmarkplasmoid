import QtQuick 2.0

Item {
    id: helper_item
    function is_this_file_a_pdf(file_url)
    {
        return file_url.includes(".pdf")
    }
    function open_command_for_this_pdf(file_url)
    {
        var file_path=file_url.split("file://")[1].split(".pdf")[0]+".pdf"
        var page=file_url.split(".pdf#")[1].split(";")[0]
        var command="okular "+file_path+" -p "+page
        return command
    }
}
