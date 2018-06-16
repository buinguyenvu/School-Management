					NOTE

	1. Folder 'data' contains all the data files, you can not modify the format of them, but you can add/remove the data.

	2. Folder 'run' contains the file .exe of the project and data files, without data files, the program does not run.

	3. Folder 'source code' contains source code of the project. You can use it to check whether we copy-paste it or not.

	4. Function's utilization are defined in '.h' files.



*******************************************************************************************************************************************************************
					BUILD
		(WIN 10 PRO BUILD 17134.112' + Visual Studio Enterprise 2017).
		Because we have not tested our program in other environments.


	1. You do not have to build. We have already built it for you.


	2. You just go to 'run' folder and run the 'Group_2_1552423.exe' file.
		*********************************************************************************************************************************
		* Do not open ANY .csv file when running the .exe file. If you want to check each task, waiting ulti the process is done.	*
		* Then close the terminal and open files to check.										*
		*********************************************************************************************************************************

	3. In case that you want to check plagiarism:
		*********************************************************************************************************************************
		* Do not open ANY .csv file when building the project(can open them in visual studio).				  	*
		* If you want to check each task, waiting ulti the process is done. Then close the terminal and open files to check.	  	*
		*********************************************************************************************************************************

		i.   Create a new empty project for C++. (name of the project and name of the Solution file must be THE SAME)

		ii.  Copy all files from 'source code' & 'data' folder to destination folder of that project(where code are built).
			For example:
			Copy all files from 'source code' to 'C:\Users\Admin_File\source\repos\Project_Name\Project_Name'.
			Where, 'Admin_File' is name of admin file of your computer,
			       'Project_Name' is name of the project.

		iii. Turn the Project on.

		iv.  Right click 'Source Files' button => 'Add' => 'Existing item...'. Then add all .cpp, .h, .csv and .txt files from the link mentioned in step (ii).

		v.   Press 'F5' to Build & Run program.

		In this case, you can check if we copy the file .exe from other groups.
		BUT: make sure that the data files in the folder 'data' and data files when you build project is THE SAME.

*******************************************************************************************************************************************************************
					RUN
	1. To run program, you just type the number of the provided option. For example, when run the program, you have this menu:
	     || 1. Student       ||
	     || 2. Professor     ||
	     || 3. Administrator ||
	     || 4. Exit          ||
	     -> If you want to login with student account, you just need to input '1' and then press 'ENTER' button. Any input out of provided options is denied.
 
	
	2. When running program:
		+) With 'search' or 'delete' purposes, you have to notice about the case insensitive.
		  For example, you type 'Van A' to search 'Nguyen Van A' or its substrings.
		  If you type 'van a', it returns you another result.

		+) Turn maximize size of the command window to experience all output clearly.

		+) When a student register a course, his/her score will be 'NULL' to differ them from others(They only register or still learning the course.
		  They have not finish the course yet). If they finished their course, their Professors would mark them and they can not un-course anymore.

		+) When student un-course the course, it depends on the Score value of the subject they want to retrieve. If the Score value is 'NULL', it means that
		  they can retrieve their course. Otherwise, they finished their course so that they can not un-course.