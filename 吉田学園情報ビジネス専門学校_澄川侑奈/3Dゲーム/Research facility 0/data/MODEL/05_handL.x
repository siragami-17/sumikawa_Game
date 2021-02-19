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
 19;
 0.00039;-1.63990;1.52895;,
 0.00039;1.63162;1.52895;,
 0.00039;1.63162;-1.53718;,
 0.00039;-1.63990;-1.53718;,
 0.00039;-1.63990;-1.53718;,
 0.00039;1.63162;-1.53718;,
 2.55966;1.03162;-1.53718;,
 2.55966;-1.03990;-1.53718;,
 2.55966;1.63162;-0.93718;,
 3.15964;-1.03990;-0.93718;,
 3.15964;1.03162;-0.93718;,
 2.55966;-1.63990;-0.93718;,
 0.00039;1.63162;1.52895;,
 2.55966;1.63162;0.92895;,
 2.55966;1.03162;1.52895;,
 3.15964;1.03162;0.92895;,
 2.55966;-1.03990;1.52895;,
 2.55966;-1.63990;0.92895;,
 3.15964;-1.03990;0.92895;;
 
 18;
 4;0,1,2,3;,
 4;4,5,6,7;,
 3;8,6,5;,
 4;9,7,6,10;,
 3;4,7,11;,
 3;8,10,6;,
 3;9,11,7;,
 4;5,12,13,8;,
 3;14,13,12;,
 4;10,8,13,15;,
 3;14,15,13;,
 4;12,0,16,14;,
 3;17,16,0;,
 4;15,14,16,18;,
 3;17,18,16;,
 4;0,4,11,17;,
 4;18,17,11,9;,
 4;9,10,15,18;;
 
 MeshMaterialList {
  5;
  18;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.517600;0.517600;0.517600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.724800;0.674400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.439216;0.439216;0.439216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\depositphotos_51590121-stock-photo-mosquito-fishnet-netting.jpg";
   }
  }
 }
 MeshNormals {
  20;
  -1.000000;0.000000;0.000000;,
  0.407694;0.358962;-0.839602;,
  0.407694;-0.358962;-0.839602;,
  0.407694;0.839602;0.358962;,
  0.407694;0.839602;-0.358962;,
  0.407694;-0.358962;0.839602;,
  0.407694;0.358962;0.839602;,
  0.407694;-0.839602;-0.358962;,
  0.407694;-0.839602;0.358962;,
  0.854767;-0.366997;-0.366997;,
  0.854767;0.366997;-0.366997;,
  0.854767;0.366997;0.366997;,
  0.854767;-0.366997;0.366997;,
  0.088757;-0.378588;-0.921300;,
  0.088757;0.378588;-0.921300;,
  0.000000;1.000000;0.000000;,
  0.088757;0.921300;0.378588;,
  0.000000;-0.000000;1.000000;,
  0.088757;-0.378588;0.921300;,
  0.000000;-1.000000;-0.000000;;
  18;
  4;0,0,0,0;,
  4;13,14,1,2;,
  3;4,1,14;,
  4;9,2,1,10;,
  3;13,2,7;,
  3;4,10,1;,
  3;9,7,2;,
  4;15,16,3,4;,
  3;6,3,16;,
  4;10,4,3,11;,
  3;6,11,3;,
  4;17,18,5,6;,
  3;8,5,18;,
  4;11,6,5,12;,
  3;8,12,5;,
  4;19,19,7,8;,
  4;12,8,7,9;,
  4;9,10,11,12;;
 }
 MeshTextureCoords {
  19;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
