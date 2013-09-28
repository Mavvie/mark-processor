mark-processor
==============

This is a mark processor library and CSV parser library bundled together. It's designed for the level system used in the OCDSB, and converts a CSV with various mark information into a new CSV with overall averages for each student.

Usage
==============

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
