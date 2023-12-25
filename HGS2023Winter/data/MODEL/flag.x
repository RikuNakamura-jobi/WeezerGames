xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 78;
 0.47099;48.15780;0.00000;,
 1.86656;48.15780;-0.80573;,
 0.47099;48.15780;-1.61147;,
 0.47099;48.15780;0.00000;,
 1.86656;48.15780;0.80573;,
 0.47099;48.15780;0.00000;,
 0.47099;48.15780;1.61147;,
 0.47099;48.15780;0.00000;,
 -0.92459;48.15780;0.80573;,
 0.47099;48.15780;0.00000;,
 -0.92459;48.15780;-0.80573;,
 0.47099;48.15780;0.00000;,
 0.47099;48.15780;-1.61147;,
 0.47099;27.85472;0.00000;,
 0.47099;27.85472;-1.61147;,
 1.86656;27.85472;-0.80573;,
 0.47099;27.85472;0.00000;,
 1.86656;27.85472;0.80573;,
 0.47099;27.85472;0.00000;,
 0.47099;27.85472;1.61147;,
 0.47099;27.85472;0.00000;,
 -0.92459;27.85472;0.80573;,
 0.47099;27.85472;0.00000;,
 -0.92459;27.85472;-0.80573;,
 0.47099;27.85472;0.00000;,
 0.47099;27.85472;-1.61147;,
 -1.33799;48.15780;-0.00000;,
 -1.33799;27.85472;-0.00000;,
 -1.33799;27.85472;-0.00000;,
 -1.33799;48.15780;-0.00000;,
 -1.33799;48.15780;-0.00000;,
 -1.33799;27.85472;-0.00000;,
 -34.40271;27.85472;-0.00000;,
 -34.40271;48.15780;-0.00000;,
 -28.86219;48.15780;0.28932;,
 -28.86219;27.85472;0.28932;,
 -34.40271;48.15780;-0.00000;,
 -34.40271;27.85472;-0.00000;,
 -28.86219;27.85472;0.28932;,
 -28.86219;48.15780;0.28932;,
 -21.25497;27.85472;-0.57477;,
 -21.25497;48.15780;-0.57477;,
 -21.25497;48.15780;-0.57477;,
 -21.25497;27.85472;-0.57477;,
 -14.48848;27.85472;0.34442;,
 -14.48848;48.15780;0.34442;,
 -14.48848;48.15780;0.34442;,
 -14.48848;27.85472;0.34442;,
 -7.59613;27.85472;-0.56926;,
 -7.59613;48.15780;-0.56926;,
 -7.59613;48.15780;-0.56926;,
 -7.59613;27.85472;-0.56926;,
 0.42903;48.01207;-1.42314;,
 1.66150;48.01207;-0.71157;,
 1.66150;-1.98026;-0.71157;,
 0.42903;-1.98026;-1.42314;,
 1.66150;48.01207;0.71157;,
 1.66150;-1.98026;0.71157;,
 0.42903;48.01207;1.42314;,
 0.42903;-1.98026;1.42314;,
 -0.80345;48.01207;0.71157;,
 -0.80345;-1.98026;0.71157;,
 -0.80345;48.01207;-0.71157;,
 -0.80345;-1.98026;-0.71157;,
 0.42903;48.01207;-1.42314;,
 0.42903;-1.98026;-1.42314;,
 0.42903;48.01207;0.00000;,
 0.42903;48.01207;0.00000;,
 0.42903;48.01207;0.00000;,
 0.42903;48.01207;0.00000;,
 0.42903;48.01207;0.00000;,
 0.42903;48.01207;0.00000;,
 0.42903;-5.94684;-0.00000;,
 0.42903;-5.94684;-0.00000;,
 0.42903;-5.94684;-0.00000;,
 0.42903;-5.94684;-0.00000;,
 0.42903;-5.94684;-0.00000;,
 0.42903;-5.94684;-0.00000;;
 
 66;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,15;,
 3;16,15,17;,
 3;18,17,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,8,10;,
 3;27,23,21;,
 3;1,15,14;,
 3;1,14,2;,
 3;4,17,15;,
 3;4,15,1;,
 3;6,19,17;,
 3;6,17,4;,
 3;8,21,19;,
 3;8,19,6;,
 3;12,25,23;,
 3;12,23,10;,
 3;10,23,28;,
 3;10,28,29;,
 3;21,8,30;,
 3;21,30,31;,
 3;32,33,34;,
 3;32,34,35;,
 3;36,37,38;,
 3;36,38,39;,
 3;40,35,34;,
 3;40,34,41;,
 3;42,39,38;,
 3;42,38,43;,
 3;44,40,41;,
 3;44,41,45;,
 3;46,42,43;,
 3;46,43,47;,
 3;29,28,48;,
 3;29,48,49;,
 3;48,44,45;,
 3;48,45,49;,
 3;31,30,50;,
 3;31,50,51;,
 3;50,46,47;,
 3;50,47,51;,
 4;52,53,54,55;,
 4;53,56,57,54;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 3;66,53,52;,
 3;67,56,53;,
 3;68,58,56;,
 3;69,60,58;,
 3;70,62,60;,
 3;71,64,62;,
 3;72,55,54;,
 3;73,54,57;,
 3;74,57,59;,
 3;75,59,61;,
 3;76,61,63;,
 3;77,63,65;;
 
 MeshMaterialList {
  2;
  66;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.169412;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.379608;0.379608;0.379608;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  50;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.052147;0.000000;-0.998639;,
  -0.030461;0.000000;-0.999536;,
  -0.030461;0.000000;-0.999536;,
  0.052477;0.000000;-0.998622;,
  -0.030581;0.000000;-0.999532;,
  -0.043080;0.000000;-0.999072;,
  0.046300;0.000000;-0.998928;,
  -0.020540;0.000000;-0.999789;,
  0.500001;0.000000;-0.866025;,
  1.000000;0.000000;0.000000;,
  0.500001;0.000000;0.866025;,
  -0.653544;0.000000;0.756888;,
  -0.788328;0.000000;0.615254;,
  -0.499999;0.000000;0.866026;,
  -0.499999;0.000000;0.866026;,
  -0.499999;0.000000;-0.866026;,
  -0.653544;0.000000;-0.756888;,
  -0.788328;0.000000;-0.615254;,
  -0.985689;0.000000;-0.168575;,
  -0.985689;0.000000;0.168576;,
  -0.052147;0.000000;0.998639;,
  0.030461;0.000000;0.999536;,
  0.030461;0.000000;0.999536;,
  0.030581;0.000000;0.999532;,
  -0.052477;0.000000;0.998622;,
  -0.046300;0.000000;0.998928;,
  0.043080;0.000000;0.999072;,
  0.090589;0.000000;-0.995888;,
  0.090589;0.000000;-0.995888;,
  -0.090589;0.000000;0.995888;,
  -0.090589;0.000000;0.995888;,
  0.020540;0.000000;0.999789;,
  0.000000;1.000000;0.000000;,
  0.500002;0.000000;-0.866024;,
  1.000000;0.000000;0.000000;,
  0.500002;0.000000;0.866024;,
  -0.499998;0.000000;0.866027;,
  -1.000000;0.000000;0.000000;,
  0.189623;-0.225058;-0.955715;,
  0.732865;-0.225057;-0.642073;,
  0.922485;-0.225057;0.313641;,
  0.189623;-0.225058;0.955715;,
  -0.732862;-0.225059;0.642076;,
  -0.922484;-0.225059;-0.313642;,
  0.815149;-0.337703;-0.470625;,
  -0.499998;0.000000;-0.866027;,
  0.000002;-0.337705;0.941252;,
  -0.815147;-0.337706;-0.470627;;
  66;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;0,0,0;,
  3;1,1,1;,
  3;10,10,10;,
  3;10,10,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,14,15;,
  3;13,15,16;,
  3;17,17,18;,
  3;17,18,19;,
  3;19,18,20;,
  3;19,20,21;,
  3;14,13,21;,
  3;14,21,20;,
  3;2,2,3;,
  3;2,3,4;,
  3;22,22,23;,
  3;22,23,24;,
  3;6,4,3;,
  3;6,3,5;,
  3;25,24,23;,
  3;25,23,26;,
  3;8,6,5;,
  3;8,5,7;,
  3;27,25,26;,
  3;27,26,28;,
  3;29,30,9;,
  3;29,9,9;,
  3;9,8,7;,
  3;9,7,9;,
  3;31,32,33;,
  3;31,33,33;,
  3;33,27,28;,
  3;33,28,33;,
  4;35,35,41,40;,
  4;36,36,42,36;,
  4;37,37,43,37;,
  4;38,38,44,38;,
  4;39,39,45,39;,
  4;47,47,47,47;,
  3;34,34,34;,
  3;34,34,34;,
  3;34,34,34;,
  3;34,34,34;,
  3;34,34,34;,
  3;34,34,34;,
  3;46,40,41;,
  3;46,41,42;,
  3;48,42,43;,
  3;48,43,44;,
  3;49,44,45;,
  3;49,45,40;;
 }
 MeshTextureCoords {
  78;
  0.083333;0.000000;,
  0.166667;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.333333;0.000000;,
  0.416667;0.000000;,
  0.500000;0.000000;,
  0.583333;0.000000;,
  0.666667;0.000000;,
  0.750000;0.000000;,
  0.833333;0.000000;,
  0.916667;0.000000;,
  1.000000;0.000000;,
  0.083333;1.000000;,
  0.000000;1.000000;,
  0.166667;1.000000;,
  0.250000;1.000000;,
  0.333333;1.000000;,
  0.416667;1.000000;,
  0.500000;1.000000;,
  0.583333;1.000000;,
  0.666667;1.000000;,
  0.750000;1.000000;,
  0.833333;1.000000;,
  0.916667;1.000000;,
  1.000000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.833333;1.000000;,
  0.833333;0.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.833333;1.000000;,
  0.833333;0.000000;,
  0.833333;0.000000;,
  0.833333;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.666667;1.000000;,
  0.666667;0.000000;,
  0.833333;1.000000;,
  0.833333;0.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.833333;1.000000;,
  0.833333;0.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.833333;1.000000;,
  0.833333;0.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.000000;0.000000;,
  0.166667;0.000000;,
  0.166667;1.000000;,
  0.000000;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.833333;0.000000;,
  0.833333;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083333;0.000000;,
  0.250000;0.000000;,
  0.416667;0.000000;,
  0.583333;0.000000;,
  0.750000;0.000000;,
  0.916667;0.000000;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;;
 }
}