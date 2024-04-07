Simple implementation of ls (list command). Well, this is not the copy of the one from linux. But open for extension, including adding other commands.

ls
    NAME
                  ls - list directory contents
    SYNOPSIS"
                  ls [OPTION]... [FILE]
    DESCRIPTION
    List information about the FILEs
    OPTION:
    -t shows type of the file
    -s shows size of the file(by default bytes)
       can accept one of the following arguments:
       kb   (kilobytes)
       mb   (megabytes)
       gb   (gigabytes)
       tb   (terrabytes)
    -p shows standard permissions related to users/groups
    -h shows this help message. Works exclusevly. This means if use
       this option along with others. Only this message will be shown
    FILE
    file path should always be presend in command and start with . or /
    EXAMPLES
    ls -stp /bin
    ls -s -t -p /bin
    ls -s kb -tp /bin;
  
