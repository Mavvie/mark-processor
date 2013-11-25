mark-processor
==============

This is a mark processor library and CSV parser library bundled together. It's designed for the level system used in the OCDSB, and converts a CSV with various mark information into a new CSV with overall averages for each student.

Usage
==============

Run the executable as follows:

#mark-processor.exe [-f filename] [-n nunits] [-e exclude] [-i restrict] [-o output]#

filename: The path to the input CSV file
nunits: The number of units to include while marking
exclude: The name of any student(s) that you want to exclude from the output. For example, -e tyler would exclude any student whose name that has "tyler" in it.
restrict: The opposite of exclude...only students whose names match restrict are output. Meaning, -i tyler would exclude every student whose name <b>doesn't</b> have "tyler" in it.
output: The path to the output CSV file (doesn't have to exist, but will overwrite if it does).

The first 2 columns are the student's last and first name.
Any following columns will be ignored unless their header is "O.A"
A CSV with the following headers:

Input
--------------
<table>
  <tr>
    <th>Header:</th>
    <th>Type</th>
    <th>a</th>
    <th>Lalala (this gets ignored)</th>
    <th>O.A</th>
    <th>O.A</th>
  </tr>
  <tr>
    <th>Value:</th>
    <td>Lastname</td>
    <td>Firstname</td>
    <td>2-</td>
    <td>4</td>
    <td>4++</td>
  </tr>
</table>

Output:
-----------------
<table>
  <tr>
    <th>Last Name</th>
    <th>First Name</th>
    <th>O.A#1</th>
    <th>O.A#2</th>
    <th>Overall Average:</th>
  </tr>
  <tr>
    <td>Lastname</td>
    <td>Firstname</td>
    <td>4</td>
    <td>4++</td>
    <td>95%</td>
  </tr>
</table>
