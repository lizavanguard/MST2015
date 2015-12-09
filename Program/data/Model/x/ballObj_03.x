xof 0303txt 0032

template Frame {
  <3d82ab46-62da-11cf-ab39-0020af71e433>
  [...]
}

template Matrix4x4 {
  <f6f23f45-7686-11cf-8f52-0040333594a3>
  array FLOAT matrix[16];
}

template FrameTransformMatrix {
  <f6f23f41-7686-11cf-8f52-0040333594a3>
  Matrix4x4 frameMatrix;
}

template Vector {
  <3d82ab5e-62da-11cf-ab39-0020af71e433>
  FLOAT x;
  FLOAT y;
  FLOAT z;
}

template MeshFace {
  <3d82ab5f-62da-11cf-ab39-0020af71e433>
  DWORD nFaceVertexIndices;
  array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
  <3d82ab44-62da-11cf-ab39-0020af71e433>
  DWORD nVertices;
  array Vector vertices[nVertices];
  DWORD nFaces;
  array MeshFace faces[nFaces];
  [...]
}

template MeshNormals {
  <f6f23f43-7686-11cf-8f52-0040333594a3>
  DWORD nNormals;
  array Vector normals[nNormals];
  DWORD nFaceNormals;
  array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
  <f6f23f44-7686-11cf-8f52-0040333594a3>
  FLOAT u;
  FLOAT v;
}

template MeshTextureCoords {
  <f6f23f40-7686-11cf-8f52-0040333594a3>
  DWORD nTextureCoords;
  array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
  <35ff44e0-6c7c-11cf-8f52-0040333594a3>
  FLOAT red;
  FLOAT green;
  FLOAT blue;
  FLOAT alpha;
}

template IndexedColor {
  <1630b820-7842-11cf-8f52-0040333594a3>
  DWORD index;
  ColorRGBA indexColor;
}

template MeshVertexColors {
  <1630b821-7842-11cf-8f52-0040333594a3>
  DWORD nVertexColors;
  array IndexedColor vertexColors[nVertexColors];
}

template VertexElement {
  <f752461c-1e23-48f6-b9f8-8350850f336f>
  DWORD Type;
  DWORD Method;
  DWORD Usage;
  DWORD UsageIndex;
}

template DeclData {
  <bf22e553-292c-4781-9fea-62bd554bdd93>
  DWORD nElements;
  array VertexElement Elements[nElements];
  DWORD nDWords;
  array DWORD data[nDWords];
}

Frame DXCC_ROOT {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
    0.000000, 1.000000, 0.000000, 0.000000,
    0.000000, 0.000000, 1.000000, 0.000000,
    0.000000, 0.000000, 0.000000, 1.000000;;
  }

  Frame RootNode {
    FrameTransformMatrix {
       1.000000, 0.000000, -0.000000, 0.000000,
      0.000000, 1.000000, -0.000000, 0.000000,
      -0.000000, -0.000000, 1.000000, -0.000000,
      0.000000, 0.000000, -0.000000, 1.000000;;
    }

    Frame ballObj_geo {
      FrameTransformMatrix {
         1.000000, 0.000000, -0.000000, 0.000000,
        0.000000, 1.000000, -0.000000, 0.000000,
        -0.000000, -0.000000, 1.000000, -0.000000,
        0.000000, 0.000000, -0.000000, 1.000000;;
      }

      Mesh _mShape {
        167;
        -67.124519;-75.515053;162.053162;,
        67.124680;-75.515053;162.053070;,
        0.000089;-75.515053;175.405029;,
        -124.030037;-75.515053;124.030144;,
        124.030151;-75.515053;124.030014;,
        -162.053101;-75.515053;67.124664;,
        162.053162;-75.515053;67.124512;,
        -175.405029;-75.515053;0.000064;,
        175.405029;-75.515053;0.000002;,
        -162.053146;-75.515053;-67.124542;,
        162.053131;-75.515053;-67.124603;,
        124.030083;-75.515053;-124.030090;,
        -124.030121;-75.515053;-124.030060;,
        -67.124626;-75.515053;-162.053101;,
        67.124573;-75.515053;-162.053131;,
        -0.000026;-75.515053;-175.405029;,
        -53.303207;-75.037338;-32.814068;,
        53.303207;-75.037338;-32.814068;,
        34.330620;-33.897308;-13.841484;,
        -34.330620;-33.897308;-13.841484;,
        34.330620;-33.897308;-13.841484;,
        34.330620;-33.897308;54.819756;,
        -34.330620;-33.897308;-13.841484;,
        -34.330620;-33.897308;54.819756;,
        53.303207;-75.037338;73.792343;,
        -53.303207;-75.037338;73.792343;,
        -34.330620;-33.897308;54.819756;,
        34.330620;-33.897308;54.819756;,
        34.330620;-33.897308;54.819756;,
        34.330620;-33.897308;-13.841484;,
        53.303207;-75.037338;-32.814068;,
        53.303207;-75.037338;73.792343;,
        -53.303207;-75.037338;-32.814068;,
        -34.330620;-33.897308;54.819756;,
        -53.303207;-75.037338;73.792343;,
        -34.330620;-33.897308;-13.841484;,
        -61.219490;-128.322998;147.797165;,
        0.000081;-128.322998;159.974457;,
        61.219635;-128.322998;147.797089;,
        -113.118973;-128.322998;113.119049;,
        113.119072;-128.322998;113.118950;,
        -147.797089;-128.322998;61.219627;,
        147.797165;-128.322998;61.219486;,
        159.974457;-128.322998;0.000002;,
        -159.974457;-128.322998;0.000059;,
        -147.797134;-128.322998;-61.219521;,
        147.797134;-128.322998;-61.219582;,
        113.119019;-128.322998;-113.119011;,
        -113.119026;-128.322998;-113.118988;,
        61.219547;-128.322998;-147.797119;,
        -61.219589;-128.322998;-147.797119;,
        -0.000024;-128.322998;-159.974457;,
        61.219635;-128.322998;147.797089;,
        0.000088;-75.515053;173.853394;,
        66.530884;-75.515053;160.619553;,
        0.000081;-128.322998;159.974457;,
        113.119072;-128.322998;113.118950;,
        122.932983;-75.515053;122.932846;,
        147.797165;-128.322998;61.219486;,
        160.619644;-75.515053;66.530724;,
        173.853394;-75.515053;0.000002;,
        159.974457;-128.322998;0.000002;,
        -61.219490;-128.322998;147.797165;,
        0.000088;-75.515053;173.853394;,
        0.000081;-128.322998;159.974457;,
        -66.530731;-75.515053;160.619629;,
        -113.118973;-128.322998;113.119049;,
        -122.932861;-75.515053;122.932961;,
        -160.619553;-75.515053;66.530869;,
        -147.797089;-128.322998;61.219627;,
        -173.853394;-75.515053;0.000064;,
        -159.974457;-128.322998;0.000059;,
        -0.000026;-75.515053;-173.853394;,
        -61.219589;-128.322998;-147.797119;,
        -0.000024;-128.322998;-159.974457;,
        -66.530838;-75.515053;-160.619583;,
        -113.119026;-128.322998;-113.118988;,
        -122.932938;-75.515053;-122.932892;,
        -160.619598;-75.515053;-66.530746;,
        -147.797134;-128.322998;-61.219521;,
        -173.853394;-75.515053;0.000064;,
        -159.974457;-128.322998;0.000059;,
        66.530792;-75.515053;-160.619598;,
        -0.000026;-75.515053;-173.853394;,
        61.219547;-128.322998;-147.797119;,
        122.932907;-75.515053;-122.932907;,
        113.119019;-128.322998;-113.119011;,
        -0.000024;-128.322998;-159.974457;,
        160.619598;-75.515053;-66.530815;,
        147.797134;-128.322998;-61.219582;,
        173.853394;-75.515053;0.000002;,
        159.974457;-128.322998;0.000002;,
        19.836929;-22.670471;41.486805;,
        26.034111;-33.326511;43.500397;,
        19.836929;-33.326511;41.486809;,
        26.034111;-22.670471;43.500389;,
        19.836929;-33.326511;34.970707;,
        19.836929;-22.670471;41.486805;,
        19.836929;-33.326511;41.486809;,
        19.836929;-22.670471;34.970707;,
        26.034111;-22.670471;32.957119;,
        19.836929;-22.670471;34.970707;,
        19.836929;-33.326511;34.970707;,
        26.034111;-33.326511;32.957119;,
        29.864178;-33.326511;38.228760;,
        29.864178;-22.670471;38.228756;,
        26.034111;-33.326511;32.957119;,
        26.034111;-22.670471;32.957119;,
        26.034111;-33.326511;43.500397;,
        26.034111;-22.670471;43.500389;,
        29.864178;-33.326511;38.228760;,
        29.864178;-22.670471;38.228756;,
        29.864178;-22.670471;38.228756;,
        19.836929;-22.670471;34.970707;,
        26.034111;-22.670471;32.957119;,
        26.034111;-22.670471;43.500389;,
        19.836929;-22.670471;41.486805;,
        -19.046579;-33.326511;41.486809;,
        -19.046579;-22.670471;41.486805;,
        -12.849398;-33.326511;43.500397;,
        -12.849398;-22.670471;43.500389;,
        -19.046579;-33.326511;34.970707;,
        -19.046579;-22.670471;41.486805;,
        -19.046579;-33.326511;41.486809;,
        -19.046579;-22.670471;34.970707;,
        -12.849398;-22.670471;32.957119;,
        -19.046579;-22.670471;34.970707;,
        -19.046579;-33.326511;34.970707;,
        -12.849398;-33.326511;32.957119;,
        -9.019331;-33.326511;38.228760;,
        -9.019331;-22.670471;38.228756;,
        -12.849398;-33.326511;32.957119;,
        -12.849398;-22.670471;32.957119;,
        -12.849398;-33.326511;43.500397;,
        -12.849398;-22.670471;43.500389;,
        -9.019331;-33.326511;38.228760;,
        -9.019331;-22.670471;38.228756;,
        -9.019331;-22.670471;38.228756;,
        -19.046579;-22.670471;34.970707;,
        -12.849398;-22.670471;32.957119;,
        -12.849398;-22.670471;43.500389;,
        -19.046579;-22.670471;41.486805;,
        -29.820847;-33.326511;13.736502;,
        -29.820847;-22.670471;13.736498;,
        -23.623667;-33.326511;15.750089;,
        -23.623667;-22.670471;15.750084;,
        -29.820847;-33.326511;7.220400;,
        -29.820847;-22.670471;13.736498;,
        -29.820847;-33.326511;13.736502;,
        -29.820847;-22.670471;7.220398;,
        -23.623667;-22.670471;5.206810;,
        -29.820847;-22.670471;7.220398;,
        -29.820847;-33.326511;7.220400;,
        -23.623667;-33.326511;5.206812;,
        -19.793598;-33.326511;10.478452;,
        -19.793598;-22.670471;10.478447;,
        -23.623667;-33.326511;5.206812;,
        -23.623667;-22.670471;5.206810;,
        -23.623667;-33.326511;15.750089;,
        -23.623667;-22.670471;15.750084;,
        -19.793598;-33.326511;10.478452;,
        -19.793598;-22.670471;10.478447;,
        -19.793598;-22.670471;10.478447;,
        -29.820847;-22.670471;7.220398;,
        -23.623667;-22.670471;5.206810;,
        -23.623667;-22.670471;15.750084;,
        -29.820847;-22.670471;13.736498;;
        109;
        3;2,1,0;,
        3;0,1,3;,
        3;1,4,3;,
        3;3,4,5;,
        3;4,6,5;,
        3;5,6,7;,
        3;8,7,6;,
        3;7,8,9;,
        3;8,10,9;,
        3;10,11,9;,
        3;12,9,11;,
        3;13,12,11;,
        3;14,13,11;,
        3;15,13,14;,
        3;18,17,16;,
        3;19,18,16;,
        3;22,21,20;,
        3;23,21,22;,
        3;26,25,24;,
        3;27,26,24;,
        3;30,29,28;,
        3;28,31,30;,
        3;34,33,32;,
        3;35,32,33;,
        3;38,37,36;,
        3;36,39,38;,
        3;38,39,40;,
        3;39,41,40;,
        3;40,41,42;,
        3;44,43,41;,
        3;42,41,43;,
        3;46,43,45;,
        3;44,45,43;,
        3;48,47,45;,
        3;46,45,47;,
        3;47,48,49;,
        3;50,49,48;,
        3;50,51,49;,
        3;54,53,52;,
        3;55,52,53;,
        3;52,56,54;,
        3;57,54,56;,
        3;59,56,58;,
        3;57,56,59;,
        3;61,60,58;,
        3;59,58,60;,
        3;64,63,62;,
        3;65,62,63;,
        3;62,65,66;,
        3;67,66,65;,
        3;69,66,68;,
        3;67,68,66;,
        3;68,70,69;,
        3;71,69,70;,
        3;74,73,72;,
        3;75,72,73;,
        3;73,76,75;,
        3;77,75,76;,
        3;78,77,76;,
        3;79,78,76;,
        3;80,78,79;,
        3;81,80,79;,
        3;84,83,82;,
        3;86,82,85;,
        3;86,84,82;,
        3;84,87,83;,
        3;85,88,86;,
        3;89,86,88;,
        3;88,90,89;,
        3;91,89,90;,
        3;94,93,92;,
        3;95,92,93;,
        3;98,97,96;,
        3;99,96,97;,
        3;102,101,100;,
        3;103,102,100;,
        3;106,105,104;,
        3;105,106,107;,
        3;110,109,108;,
        3;109,110,111;,
        3;114,113,112;,
        3;113,115,112;,
        3;116,115,113;,
        3;119,118,117;,
        3;120,118,119;,
        3;123,122,121;,
        3;124,121,122;,
        3;127,126,125;,
        3;128,127,125;,
        3;131,130,129;,
        3;130,131,132;,
        3;135,134,133;,
        3;134,135,136;,
        3;139,138,137;,
        3;138,140,137;,
        3;141,140,138;,
        3;144,143,142;,
        3;145,143,144;,
        3;148,147,146;,
        3;149,146,147;,
        3;152,151,150;,
        3;153,152,150;,
        3;156,155,154;,
        3;155,156,157;,
        3;160,159,158;,
        3;159,160,161;,
        3;164,163,162;,
        3;163,165,162;,
        3;166,165,163;;

        MeshMaterialList {
          1;
          109;
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
          Material {
            1.0; 1.0; 1.0; 1.000000;;
            1.000000;
            0.000000; 0.000000; 0.000000;;
            0.000000; 0.000000; 0.000000;;
            TextureFilename { "ballTex.png"; }
          }
        }

        MeshNormals {
        167;
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;0.000001;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;-0.000001;,
        -0.000000;-0.418783;0.908086;,
        -0.000000;-0.418783;0.908086;,
        -0.000000;-0.418783;0.908086;,
        -0.000000;-0.418783;0.908086;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-0.418783;-0.908086;,
        -0.000000;-0.418783;-0.908086;,
        -0.000000;-0.418783;-0.908086;,
        -0.000000;-0.418783;-0.908086;,
        -0.908086;-0.418783;0.000000;,
        -0.908086;-0.418783;0.000000;,
        -0.908086;-0.418783;0.000000;,
        -0.908086;-0.418783;0.000000;,
        0.908086;-0.418783;0.000000;,
        0.908086;-0.418783;0.000000;,
        0.908086;-0.418783;0.000000;,
        0.908086;-0.418783;0.000000;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;-0.000001;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;-0.000000;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;-0.000000;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;-0.000000;,
        -0.000000;1.000000;0.000000;,
        -0.000000;1.000000;-0.000001;,
        -0.000000;1.000000;-0.000001;,
        -0.000000;1.000000;-0.000001;,
        -0.365824;0.254184;-0.895301;,
        -0.000001;0.254187;-0.967155;,
        -0.366183;0.254185;-0.895154;,
        -0.000001;0.254187;-0.967155;,
        -0.683882;0.254187;-0.683882;,
        -0.683882;0.254187;-0.683882;,
        -0.895301;0.254184;-0.365823;,
        -0.895154;0.254185;-0.366183;,
        -0.967155;0.254187;0.000000;,
        -0.967155;0.254187;0.000000;,
        0.365823;0.254184;-0.895301;,
        -0.000001;0.254187;-0.967155;,
        -0.000001;0.254187;-0.967155;,
        0.366182;0.254185;-0.895154;,
        0.683882;0.254187;-0.683882;,
        0.683882;0.254187;-0.683882;,
        0.895154;0.254185;-0.366183;,
        0.895301;0.254184;-0.365824;,
        0.967155;0.254187;-0.000000;,
        0.967155;0.254186;-0.000000;,
        0.000000;0.254187;0.967155;,
        0.365823;0.254184;0.895301;,
        -0.000000;0.254187;0.967155;,
        0.366183;0.254185;0.895154;,
        0.683882;0.254187;0.683882;,
        0.683882;0.254187;0.683882;,
        0.895154;0.254185;0.366183;,
        0.895301;0.254184;0.365823;,
        0.967155;0.254187;-0.000000;,
        0.967155;0.254186;-0.000000;,
        -0.366183;0.254185;0.895154;,
        0.000000;0.254187;0.967155;,
        -0.365823;0.254184;0.895301;,
        -0.683882;0.254187;0.683882;,
        -0.683882;0.254187;0.683882;,
        -0.000000;0.254187;0.967155;,
        -0.895154;0.254185;0.366183;,
        -0.895301;0.254184;0.365823;,
        -0.967155;0.254187;0.000000;,
        -0.967155;0.254187;0.000000;,
        0.309017;-0.000001;-0.951057;,
        0.309016;-0.000000;-0.951057;,
        0.309016;-0.000000;-0.951057;,
        0.309017;-0.000001;-0.951057;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        0.309017;-0.000000;0.951056;,
        0.309018;-0.000000;0.951056;,
        0.309017;-0.000000;0.951056;,
        0.309017;-0.000000;0.951057;,
        -0.809017;-0.000000;0.587785;,
        -0.809017;-0.000000;0.587785;,
        -0.809017;-0.000000;0.587785;,
        -0.809017;-0.000000;0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        0.309016;-0.000000;-0.951057;,
        0.309017;-0.000001;-0.951057;,
        0.309016;-0.000000;-0.951057;,
        0.309017;-0.000001;-0.951057;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        0.309017;-0.000000;0.951056;,
        0.309018;-0.000000;0.951056;,
        0.309017;-0.000000;0.951056;,
        0.309017;-0.000000;0.951057;,
        -0.809017;0.000000;0.587785;,
        -0.809017;0.000000;0.587785;,
        -0.809017;0.000000;0.587785;,
        -0.809017;-0.000000;0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;,
        0.309017;-0.000000;-0.951056;,
        0.309017;-0.000000;-0.951057;,
        0.309017;-0.000000;-0.951057;,
        0.309016;-0.000000;-0.951057;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        1.000000;-0.000000;0.000000;,
        0.309017;0.000000;0.951056;,
        0.309017;0.000000;0.951056;,
        0.309017;0.000000;0.951056;,
        0.309017;0.000000;0.951056;,
        -0.809017;0.000000;0.587785;,
        -0.809017;0.000000;0.587785;,
        -0.809017;0.000000;0.587785;,
        -0.809017;0.000000;0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.809017;-0.000000;-0.587785;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -0.000000;-1.000000;0.000000;,
        -0.000000;-1.000000;0.000000;;
        109;
        3;2,1,0;,
        3;0,1,3;,
        3;1,4,3;,
        3;3,4,5;,
        3;4,6,5;,
        3;5,6,7;,
        3;8,7,6;,
        3;7,8,9;,
        3;8,10,9;,
        3;10,11,9;,
        3;12,9,11;,
        3;13,12,11;,
        3;14,13,11;,
        3;15,13,14;,
        3;18,17,16;,
        3;19,18,16;,
        3;22,21,20;,
        3;23,21,22;,
        3;26,25,24;,
        3;27,26,24;,
        3;30,29,28;,
        3;28,31,30;,
        3;34,33,32;,
        3;35,32,33;,
        3;38,37,36;,
        3;36,39,38;,
        3;38,39,40;,
        3;39,41,40;,
        3;40,41,42;,
        3;44,43,41;,
        3;42,41,43;,
        3;46,43,45;,
        3;44,45,43;,
        3;48,47,45;,
        3;46,45,47;,
        3;47,48,49;,
        3;50,49,48;,
        3;50,51,49;,
        3;54,53,52;,
        3;55,52,53;,
        3;52,56,54;,
        3;57,54,56;,
        3;59,56,58;,
        3;57,56,59;,
        3;61,60,58;,
        3;59,58,60;,
        3;64,63,62;,
        3;65,62,63;,
        3;62,65,66;,
        3;67,66,65;,
        3;69,66,68;,
        3;67,68,66;,
        3;68,70,69;,
        3;71,69,70;,
        3;74,73,72;,
        3;75,72,73;,
        3;73,76,75;,
        3;77,75,76;,
        3;78,77,76;,
        3;79,78,76;,
        3;80,78,79;,
        3;81,80,79;,
        3;84,83,82;,
        3;86,82,85;,
        3;86,84,82;,
        3;84,87,83;,
        3;85,88,86;,
        3;89,86,88;,
        3;88,90,89;,
        3;91,89,90;,
        3;94,93,92;,
        3;95,92,93;,
        3;98,97,96;,
        3;99,96,97;,
        3;102,101,100;,
        3;103,102,100;,
        3;106,105,104;,
        3;105,106,107;,
        3;110,109,108;,
        3;109,110,111;,
        3;114,113,112;,
        3;113,115,112;,
        3;116,115,113;,
        3;119,118,117;,
        3;120,118,119;,
        3;123,122,121;,
        3;124,121,122;,
        3;127,126,125;,
        3;128,127,125;,
        3;131,130,129;,
        3;130,131,132;,
        3;135,134,133;,
        3;134,135,136;,
        3;139,138,137;,
        3;138,140,137;,
        3;141,140,138;,
        3;144,143,142;,
        3;145,143,144;,
        3;148,147,146;,
        3;149,146,147;,
        3;152,151,150;,
        3;153,152,150;,
        3;156,155,154;,
        3;155,156,157;,
        3;160,159,158;,
        3;159,160,161;,
        3;164,163,162;,
        3;163,165,162;,
        3;166,165,163;;
        }

        MeshTextureCoords {
        167;
        0.335913;0.468786;,
        0.153336;0.468786;,
        0.244624;0.486944;,
        0.413303;0.417075;,
        0.075946;0.417075;,
        0.465014;0.339685;,
        0.024235;0.339685;,
        0.483172;0.248397;,
        0.006077;0.248397;,
        0.465014;0.157109;,
        0.024235;0.157109;,
        0.075946;0.079719;,
        0.413303;0.079718;,
        0.335912;0.028008;,
        0.153336;0.028008;,
        0.244624;0.009849;,
        0.024420;0.985000;,
        0.334254;0.985000;,
        0.279114;0.884787;,
        0.079561;0.884787;,
        0.276804;0.858919;,
        0.276804;0.659367;,
        0.077252;0.858919;,
        0.077252;0.659367;,
        0.024420;0.985000;,
        0.334254;0.985000;,
        0.279114;0.884787;,
        0.079561;0.884787;,
        0.279114;0.884787;,
        0.079561;0.884787;,
        0.024420;0.985000;,
        0.334254;0.985000;,
        0.334254;0.985000;,
        0.079561;0.884787;,
        0.024420;0.985000;,
        0.279113;0.884787;,
        0.115615;0.498721;,
        0.088887;0.493404;,
        0.062159;0.498721;,
        0.138274;0.513861;,
        0.039500;0.513861;,
        0.153414;0.536520;,
        0.024359;0.536520;,
        0.019043;0.563248;,
        0.158731;0.563248;,
        0.153414;0.589976;,
        0.024359;0.589976;,
        0.039500;0.612635;,
        0.138274;0.612635;,
        0.062159;0.627776;,
        0.115615;0.627776;,
        0.088887;0.633092;,
        0.062159;0.498721;,
        0.088887;0.487345;,
        0.059840;0.493122;,
        0.088887;0.493404;,
        0.039500;0.513861;,
        0.035215;0.509576;,
        0.024359;0.536520;,
        0.018761;0.534201;,
        0.012983;0.563248;,
        0.019043;0.563248;,
        0.115615;0.498721;,
        0.088887;0.487345;,
        0.088887;0.493404;,
        0.117934;0.493122;,
        0.138274;0.513861;,
        0.142559;0.509576;,
        0.159013;0.534201;,
        0.153414;0.536520;,
        0.164790;0.563248;,
        0.158731;0.563248;,
        0.088887;0.639152;,
        0.115615;0.627776;,
        0.088887;0.633092;,
        0.117934;0.633374;,
        0.138274;0.612635;,
        0.142559;0.616920;,
        0.159013;0.592295;,
        0.153414;0.589976;,
        0.164790;0.563248;,
        0.158731;0.563248;,
        0.059840;0.633374;,
        0.088887;0.639152;,
        0.062159;0.627776;,
        0.035215;0.616920;,
        0.039500;0.612635;,
        0.088887;0.633092;,
        0.018761;0.592295;,
        0.024359;0.589976;,
        0.012983;0.563248;,
        0.019043;0.563248;,
        0.957711;0.149306;,
        0.922381;0.240628;,
        0.957711;0.240628;,
        0.922381;0.149306;,
        0.808569;0.240628;,
        0.775066;0.149306;,
        0.775066;0.240628;,
        0.808569;0.149306;,
        0.843899;0.149306;,
        0.808569;0.149306;,
        0.808569;0.240628;,
        0.843899;0.240628;,
        0.883140;0.240628;,
        0.883140;0.149306;,
        0.843899;0.240628;,
        0.843899;0.149306;,
        0.922381;0.240628;,
        0.922381;0.149306;,
        0.883140;0.240628;,
        0.883140;0.149306;,
        0.755285;0.192893;,
        0.673421;0.219493;,
        0.724016;0.235932;,
        0.724016;0.149855;,
        0.673421;0.166294;,
        0.957711;0.240628;,
        0.957711;0.149306;,
        0.922381;0.240628;,
        0.922381;0.149306;,
        0.808569;0.240628;,
        0.775066;0.149306;,
        0.775066;0.240628;,
        0.808569;0.149306;,
        0.843899;0.149306;,
        0.808569;0.149306;,
        0.808569;0.240628;,
        0.843899;0.240628;,
        0.883140;0.240628;,
        0.883140;0.149306;,
        0.843899;0.240628;,
        0.843899;0.149306;,
        0.922381;0.240628;,
        0.922381;0.149306;,
        0.883140;0.240628;,
        0.883140;0.149306;,
        0.755285;0.192893;,
        0.673421;0.219493;,
        0.724016;0.235932;,
        0.724016;0.149855;,
        0.673421;0.166294;,
        0.957711;0.240628;,
        0.957711;0.149306;,
        0.922381;0.240628;,
        0.922381;0.149306;,
        0.808569;0.240628;,
        0.775066;0.149306;,
        0.775066;0.240628;,
        0.808569;0.149306;,
        0.843899;0.149306;,
        0.808569;0.149306;,
        0.808569;0.240628;,
        0.843899;0.240628;,
        0.883140;0.240628;,
        0.883140;0.149306;,
        0.843899;0.240628;,
        0.843899;0.149306;,
        0.922381;0.240628;,
        0.922381;0.149306;,
        0.883140;0.240628;,
        0.883140;0.149306;,
        0.755285;0.192893;,
        0.673421;0.219493;,
        0.724016;0.235932;,
        0.724016;0.149855;,
        0.673421;0.166294;;
        }
      }

    }

  }

}
