Simple implementation of ls (list command). Well, this is not the copy of the one from linux. But open for extension, including adding other commands.<br />

ls<br />
    NAME<br />
                  ls - list directory contents<br />
    SYNOPSIS<br />
                  ls [OPTION]... [FILE]<br />
    DESCRIPTION<br />
    List information about the FILEs<br />
    OPTION:<br />
    -t shows type of the file<br />
    -s shows size of the file(by default bytes)<br />
       can accept one of the following arguments:<br />
       kb   (kilobytes)<br />
       mb   (megabytes)<br />
       gb   (gigabytes)<br />
       tb   (terrabytes)<br />
    -p shows standard permissions related to users/groups<br />
    -h shows this help message. Works exclusevly. This means if use<br />
       this option along with others. Only this message will be shown<br />
    FILE<br />
    file path should always be presend in command and start with . or /<br />
    EXAMPLES<br />
    ls -stp /bin<br />
    ls -s -t -p /bin<br />
    ls -s kb -tp /bin;<br />
  
