Table table;

void setup() {
  table = new Table();
  table.addColumn("Height");
  table.addColumn("Width");
  selectFolder("Select a folder to process:", "folderSelected");
}

void folderSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
  }
  File[] files = listFiles(selection);

for (int i = 0; i < files.length; i++) {
    File f = files[i];
    processImage(f);
    println("#" + i + " Name: " + f.getName());
    println("-----------------------");
  }
}

// This function returns all the files in a directory as an array of File objects
// This is useful if you want more info about the file

File[] listFiles(String dir) {
  File file = new File(dir);
  if (file.isDirectory()) {
    File[] files = file.listFiles();
    return files;
  } else {
    // If it's not a directory
    return null;
  }
}

void processImage(File image){

  String      filename, basename, filenameBin, filenameCsv;
  PImage      img;
  PrintWriter output;
  int         i, x, y, b, rowBytes, totalBytes, lastBit, sum, n, r=1;
  byte[] data;
  int byteIndex = 0;

  // Select and load image
  println("Loading image...");
  filename = image.getPath();
  img      = loadImage(image.getPath());

  TableRow newRow = table.addRow();
  newRow.setInt("Height", img.height);
  newRow.setInt("Width", img.width);



  // Morph filename into output filename and base name for data
  x = filename.lastIndexOf('.');
  if (x > 0) filename = filename.substring(0, x);  // Strip current extension
  x = filename.lastIndexOf('/');
  if (x > 0) basename = filename.substring(x + 1); // Strip path
  else      basename = filename;

  filenameCsv = filename+".csv";
  saveTable(table, filenameCsv);
  table.removeRow(0);  // Removes the first row
  filenameBin = filename+".bin";

  println("Writing output to " + filenameBin);

  // Calculate output size
  rowBytes   = (img.width + 7) / 8;
  totalBytes = rowBytes * img.height;

  //Create array for bytes
  data = new byte[totalBytes];

  // Convert image to B&W, make pixels readable
  img.filter(THRESHOLD);
  img.loadPixels();

  // Generate body of array
  for (i=n=y=0; y<img.height; y++) { // Each row...
    //    output.print("\n  ");
    for (x=0; x<rowBytes; x++) { // Each 8-pixel block within row...
      lastBit = (x < rowBytes - 1) ? 1 : (1 << (rowBytes * 8 - img.width));
      sum     = 0; // Clear accumulated 8 bits
      for (b=128; b>=lastBit; b >>= 1) { // Each pixel within block...
        if ((img.pixels[i++] & 1) == 0) sum |= b; // If black pixel, set bit
      }

      //Write to byte array
      data[byteIndex] = byte(sum);
        if (byteIndex > 0) {
          data[byteIndex] = byte(data[byteIndex-1] << 8 | data[byteIndex]);
//                println("byteIndex "+(byteIndex-1)+": "+data[byteIndex-1]);
        }
      byteIndex++;
    }
  }

  // save byte array as binary file
  saveBytes(filenameBin, data);

  println("Done!");
}
