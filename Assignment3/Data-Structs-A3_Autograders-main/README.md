# Currently broken, fixing it rn How to Run

### Step 1: Downloading the Script

- **GUI Interface**:  
  If you're using a GUI interface, simply press the "Code" button and download the ZIP file.  
  Then, extract the contents to your desired location.

- **Terminal Interface**:  
  If you're using a terminal, download the program by running the following command:

  ```bash
  wget https://github.com/AlphaCloudX/Data-Structs-A3_Autograders/archive/refs/heads/main.zip
  ```
  After downloading, extract the ZIP file with:
  ```bash
  unzip main.zip
  ```

    Then navigate to where your MakeFile is and comile your project to get the a3q2 executable:
  ```bash
  cd /where/your/make/file/is
  ```

  Then compile
  ```bash
  make
  ```

  Then to keep track of where the executable is located run:
  ```bash
  pwd
  ```

  Now navigate back up to where the unzipped autograder is, might require doing `c..` a few times, Then navigate inside the folder:
  ```bash
  cd Data-Structs-A3_Autograders-main/q2
  ```

  Then copy your a3q2 inside of here.
  ```bash
  cp /path/to/source/a3q2 .
  ```


### Step 2: Provide the Executable File

Before running the script, ensure that the `.exe` or `.out` file is copied into the `q2` folder. Can be done via terminal or gui.

Once the file is in the folder, when prompted, enter the filename of the executable (e.g., `yourfile.exe` or `yourfile.out`).

### Step 2: Run the Script

To execute the program, use the following command:

```bash
python q2.py
```

or

```bash
python3 q2.py
```

### Additional Information

- This program is designed to process **1000 test cases**.
- Currently Testing To Validate Results
