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
 30;
 -34.27811;0.63227;-2.56251;,
 34.27811;0.63227;-2.56251;,
 34.27811;0.63227;2.56251;,
 -34.27811;0.63227;2.56251;,
 -34.27811;87.25960;-2.56251;,
 34.27811;0.63227;-2.56251;,
 -34.27811;0.63227;-2.56251;,
 -17.88659;112.95999;2.56251;,
 -34.27811;87.25960;2.56251;,
 -34.27811;0.63227;2.56251;,
 34.27811;0.63227;2.56251;,
 -34.27811;87.25960;-2.56251;,
 -34.27811;0.63227;-2.56251;,
 -34.27811;87.25960;2.56251;,
 34.27811;87.25960;2.56251;,
 34.27811;0.63227;-2.56251;,
 34.27811;87.25960;-2.56251;,
 20.16823;112.95999;-2.56251;,
 34.27811;87.25960;-2.56251;,
 -17.88659;112.95999;-2.56251;,
 34.27811;87.25960;2.56251;,
 20.16823;112.95999;2.56251;,
 20.16823;112.95999;2.56251;,
 20.16823;112.95999;-2.56251;,
 -17.88659;112.95999;-2.56251;,
 -17.88659;112.95999;2.56251;,
 -34.27811;87.25960;-2.56251;,
 -34.27811;87.25960;2.56251;,
 34.27811;87.25960;2.56251;,
 34.27811;87.25960;-2.56251;;
 
 11;
 4;0,1,2,3;,
 3;4,5,6;,
 4;7,8,9,10;,
 4;11,12,3,13;,
 4;14,2,15,16;,
 4;17,18,5,4;,
 3;17,4,19;,
 4;20,21,7,10;,
 4;22,23,24,25;,
 4;24,26,27,25;,
 4;22,28,29,23;;
 
 MeshMaterialList {
  1;
  11;
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
  0;;
  Material {
   0.282353;0.087843;0.122353;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  10;
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.968654;0.248415;0.000000;,
  -0.959978;0.280076;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.480764;0.876850;0.000000;,
  0.876580;0.481255;0.000000;;
  11;
  4;0,0,0,0;,
  3;1,1,1;,
  4;2,2,2,2;,
  4;4,5,5,4;,
  4;3,6,6,3;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;2,2,2,2;,
  4;7,7,8,8;,
  4;8,4,4,8;,
  4;9,3,3,9;;
 }
 MeshTextureCoords {
  30;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.153814;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.760904;0.000000;,
  1.000000;0.153814;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.153814;,
  1.000000;1.000000;,
  0.000000;0.153814;,
  1.000000;0.228796;,
  0.000000;1.000000;,
  0.000000;0.228796;,
  0.794185;0.000000;,
  1.000000;0.228796;,
  0.239096;0.000000;,
  0.000000;0.228796;,
  0.205815;0.000000;,
  0.794185;0.000000;,
  0.794185;1.000000;,
  0.239096;1.000000;,
  0.239096;0.000000;,
  0.239096;1.000000;,
  0.239096;0.000000;,
  0.794185;0.000000;,
  0.794185;1.000000;;
 }
}
