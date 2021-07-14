import QtQuick 2.0
import QtTest 1.2
//import Bookmarkview
import "../"
TestCase {
    name: "HelperTests"
    Helper{
        id:unit
    }
    function test_is_this_file_a_pdf() {
        compare(unit.is_this_file_a_pdf("file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:2"),true, "correctly detect pdf")
        compare(unit.is_this_file_a_pdf("file:///home/VladimirPutin/Bullshit.nonpdf#20;C2:0.499632:0.302495:2"),false, "correctly discard non pdf")
    }
    function test_open_command_for_this_pdf(){
        compare(unit.open_command_for_this_pdf("file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:2"),"okular /home/VladimirPutin/Bullshit.pdf -p 20","Correct opening command using okular for a pdf")
    }
}

