//ImageProcessor to convert a set of images (*.jpg,bmp, png) to *bin
//Has some extra functionalities regarding as specific *.csv in
//our project but will work with every folder.

//Image proceeding based on work of https://github.com/treipatru/PhotoMetron
//File listing based on work of Daniel Shiffman.
//Thanks!

//(C) RaktiPiepEkti 2017 - Max von Elverfeldt

String filenameCsv;
Table table;
String[] imgNames;
boolean csv;


void setup() {
  table = new Table();
  selectFolder("Select a folder to process:", "folderSelected");
}

//Select folder with images and either "spielomat.csv" or not.
void folderSelected(File selection) {

  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    filenameCsv = selection.getAbsolutePath()+"/spielomat.csv";

  //Try to load table and ignore subsequently if none is available.
    table = loadTable(filenameCsv, "header");
    if (table!=null){
      println("Loaded table successfully");
      csv = true;
    }
    else {
      csv = false;
    }
  }


  //If *.csv is available grab filenames.
  if (csv==true){
  imgNames = new String[table.getRowCount()];
  for (int i = 0; i < imgNames.length; i++) {
    imgNames[i] = table.getString(i,"Datei");
    //imgNames[i]+=".jpg";
  }
  }

  //Write files in folder to array of files.
  File[] files = listFiles(selection);

  //Repeat processImage(_file) for every file in array.
for (int i = 0; i < files.length; i++) {
    File f = files[i];
    processImage(f);
    println("#" + i + " Name: " + f.getName());
    println("-----------------------");
  }

  //Naturally save table finally, if used before.
   if (csv==true){
   saveTable(table, filenameCsv);
 }
}

//Return array with files.
File[] listFiles(String dir) {
  File file = new File(dir);
  if (file.isDirectory()) {
    File[] files = file.listFiles();
    return files;
  } else {
    return null;
  }
}


void processImage(File image){  // Select and load image
  String      filename, basename, filenameBin;
  PImage      img;
  PrintWriter output;
  int         i, x, y, b, rowBytes, totalBytes, lastBit, sum, n, r=1;
  byte[] data;
  int byteIndex = 0;
  println("Loading image...");
  filename = image.getPath();
  img      = loadImage(image.getPath());

  if (img!=null){
  // Morph filename into output filename and base name for data
  x = filename.lastIndexOf('.');
  if (x > 0) filename = filename.substring(0, x);  // Strip current extension
  x = filename.lastIndexOf('/');
  if (x > 0) basename = filename.substring(x + 1); // Strip path
  else      basename = filename;
  print(basename);
  if (csv==true){
  for (int j = 0; j < imgNames.length; j++) {

      if (imgNames[j].equals(basename)==true){
          table.setInt(j, "Height", img.height);
          table.setInt(j, "Width", img.width);
            }
  }
}

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
else {
  println("no image loaded"); // the file selected was not an image that could be loaded
}

}
