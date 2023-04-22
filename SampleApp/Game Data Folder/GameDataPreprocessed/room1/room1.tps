<?xml version="1.0" encoding="UTF-8"?>
<data version="1.0">
    <struct type="Settings">
        <key>fileFormatVersion</key>
        <int>5</int>
        <key>texturePackerVersion</key>
        <string>6.0.0</string>
        <key>autoSDSettings</key>
        <array>
            <struct type="AutoSDSettings">
                <key>scale</key>
                <double>1</double>
                <key>extension</key>
                <string></string>
                <key>spriteFilter</key>
                <string></string>
                <key>acceptFractionalValues</key>
                <false/>
                <key>maxTextureSize</key>
                <QSize>
                    <key>width</key>
                    <int>-1</int>
                    <key>height</key>
                    <int>-1</int>
                </QSize>
            </struct>
        </array>
        <key>allowRotation</key>
        <false/>
        <key>shapeDebug</key>
        <false/>
        <key>dpi</key>
        <uint>72</uint>
        <key>dataFormat</key>
        <string>json-array</string>
        <key>textureFileName</key>
        <filename></filename>
        <key>flipPVR</key>
        <false/>
        <key>pvrQualityLevel</key>
        <uint>3</uint>
        <key>astcQualityLevel</key>
        <uint>2</uint>
        <key>basisUniversalQualityLevel</key>
        <uint>2</uint>
        <key>atfCompressData</key>
        <false/>
        <key>mipMapMinSize</key>
        <uint>32768</uint>
        <key>etc1QualityLevel</key>
        <uint>70</uint>
        <key>etc2QualityLevel</key>
        <uint>70</uint>
        <key>dxtCompressionMode</key>
        <enum type="SettingsBase::DxtCompressionMode">DXT_PERCEPTUAL</enum>
        <key>jxrColorFormat</key>
        <enum type="SettingsBase::JpegXrColorMode">JXR_YUV444</enum>
        <key>jxrTrimFlexBits</key>
        <uint>0</uint>
        <key>jxrCompressionLevel</key>
        <uint>0</uint>
        <key>ditherType</key>
        <enum type="SettingsBase::DitherType">NearestNeighbour</enum>
        <key>backgroundColor</key>
        <uint>0</uint>
        <key>libGdx</key>
        <struct type="LibGDX">
            <key>filtering</key>
            <struct type="LibGDXFiltering">
                <key>x</key>
                <enum type="LibGDXFiltering::Filtering">Linear</enum>
                <key>y</key>
                <enum type="LibGDXFiltering::Filtering">Linear</enum>
            </struct>
        </struct>
        <key>shapePadding</key>
        <uint>0</uint>
        <key>jpgQuality</key>
        <uint>80</uint>
        <key>pngOptimizationLevel</key>
        <uint>0</uint>
        <key>webpQualityLevel</key>
        <uint>101</uint>
        <key>textureSubPath</key>
        <string></string>
        <key>atfFormats</key>
        <string></string>
        <key>textureFormat</key>
        <enum type="SettingsBase::TextureFormat">png</enum>
        <key>borderPadding</key>
        <uint>0</uint>
        <key>maxTextureSize</key>
        <QSize>
            <key>width</key>
            <int>2048</int>
            <key>height</key>
            <int>2048</int>
        </QSize>
        <key>fixedTextureSize</key>
        <QSize>
            <key>width</key>
            <int>-1</int>
            <key>height</key>
            <int>-1</int>
        </QSize>
        <key>algorithmSettings</key>
        <struct type="AlgorithmSettings">
            <key>algorithm</key>
            <enum type="AlgorithmSettings::AlgorithmId">Basic</enum>
            <key>freeSizeMode</key>
            <enum type="AlgorithmSettings::AlgorithmFreeSizeMode">Best</enum>
            <key>sizeConstraints</key>
            <enum type="AlgorithmSettings::SizeConstraints">AnySize</enum>
            <key>forceSquared</key>
            <false/>
            <key>maxRects</key>
            <struct type="AlgorithmMaxRectsSettings">
                <key>heuristic</key>
                <enum type="AlgorithmMaxRectsSettings::Heuristic">Best</enum>
            </struct>
            <key>basic</key>
            <struct type="AlgorithmBasicSettings">
                <key>sortBy</key>
                <enum type="AlgorithmBasicSettings::SortBy">Best</enum>
                <key>order</key>
                <enum type="AlgorithmBasicSettings::Order">Ascending</enum>
            </struct>
            <key>polygon</key>
            <struct type="AlgorithmPolygonSettings">
                <key>alignToGrid</key>
                <uint>1</uint>
            </struct>
        </struct>
        <key>dataFileNames</key>
        <map type="GFileNameMap">
            <key>data</key>
            <struct type="DataFile">
                <key>name</key>
                <filename></filename>
            </struct>
        </map>
        <key>multiPack</key>
        <false/>
        <key>forceIdenticalLayout</key>
        <false/>
        <key>outputFormat</key>
        <enum type="SettingsBase::OutputFormat">RGBA8888</enum>
        <key>alphaHandling</key>
        <enum type="SettingsBase::AlphaHandling">ClearTransparentPixels</enum>
        <key>contentProtection</key>
        <struct type="ContentProtection">
            <key>key</key>
            <string></string>
        </struct>
        <key>autoAliasEnabled</key>
        <true/>
        <key>trimSpriteNames</key>
        <false/>
        <key>prependSmartFolderName</key>
        <false/>
        <key>autodetectAnimations</key>
        <true/>
        <key>globalSpriteSettings</key>
        <struct type="SpriteSettings">
            <key>scale</key>
            <double>1</double>
            <key>scaleMode</key>
            <enum type="ScaleMode">Fast</enum>
            <key>extrude</key>
            <uint>0</uint>
            <key>trimThreshold</key>
            <uint>1</uint>
            <key>trimMargin</key>
            <uint>1</uint>
            <key>trimMode</key>
            <enum type="SpriteSettings::TrimMode">Crop</enum>
            <key>tracerTolerance</key>
            <int>200</int>
            <key>heuristicMask</key>
            <false/>
            <key>defaultPivotPoint</key>
            <point_f>0.5,0.5</point_f>
            <key>writePivotPoints</key>
            <false/>
        </struct>
        <key>individualSpriteSettings</key>
        <map type="IndividualSpriteSettingsMap">
            <key type="filename">sprites/astar_blue.png</key>
            <key type="filename">sprites/astar_white.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>0,0,1,1</rect>
                <key>scale9Paddings</key>
                <rect>0,0,1,1</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/astar_cross1.png</key>
            <key type="filename">sprites/astar_cross2.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>1,1,1,1</rect>
                <key>scale9Paddings</key>
                <rect>1,1,1,1</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/astar_cross3.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>1,1,3,3</rect>
                <key>scale9Paddings</key>
                <rect>1,1,3,3</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/background.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>100,45,200,90</rect>
                <key>scale9Paddings</key>
                <rect>100,45,200,90</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/beam.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>97,28,194,57</rect>
                <key>scale9Paddings</key>
                <rect>97,28,194,57</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/copier_cartridge.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>2,1,4,2</rect>
                <key>scale9Paddings</key>
                <rect>2,1,4,2</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/copier_door_closed.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>6,3,11,7</rect>
                <key>scale9Paddings</key>
                <rect>6,3,11,7</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/copier_door_open.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>7,5,15,9</rect>
                <key>scale9Paddings</key>
                <rect>7,5,15,9</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/copytron.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>14,20,29,39</rect>
                <key>scale9Paddings</key>
                <rect>14,20,29,39</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/copytron_door_open_lit.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>4,5,7,11</rect>
                <key>scale9Paddings</key>
                <rect>4,5,7,11</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/copytron_lid_closed.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>12,4,25,7</rect>
                <key>scale9Paddings</key>
                <rect>12,4,25,7</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/copytron_lid_open.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>6,6,11,12</rect>
                <key>scale9Paddings</key>
                <rect>6,6,11,12</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/copytron_tube_lit.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>11,11,23,23</rect>
                <key>scale9Paddings</key>
                <rect>11,11,23,23</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/desk.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>28,9,57,17</rect>
                <key>scale9Paddings</key>
                <rect>28,9,57,17</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/door_closed.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>8,17,15,33</rect>
                <key>scale9Paddings</key>
                <rect>8,17,15,33</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/door_open.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>3,17,5,33</rect>
                <key>scale9Paddings</key>
                <rect>3,17,5,33</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/door_opening1.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>6,17,13,33</rect>
                <key>scale9Paddings</key>
                <rect>6,17,13,33</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/door_opening2.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>4,17,9,33</rect>
                <key>scale9Paddings</key>
                <rect>4,17,9,33</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/far_paper_stack.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>13,8,26,15</rect>
                <key>scale9Paddings</key>
                <rect>13,8,26,15</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/file_cabinet.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>8,17,16,35</rect>
                <key>scale9Paddings</key>
                <rect>8,17,16,35</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/five_cent_sign.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>3,5,7,11</rect>
                <key>scale9Paddings</key>
                <rect>3,5,7,11</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/foreground.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>105,20,210,39</rect>
                <key>scale9Paddings</key>
                <rect>105,20,210,39</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/hills.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>95,21,190,42</rect>
                <key>scale9Paddings</key>
                <rect>95,21,190,42</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/left_paper_stack.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>14,11,27,21</rect>
                <key>scale9Paddings</key>
                <rect>14,11,27,21</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/map.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>8,7,17,14</rect>
                <key>scale9Paddings</key>
                <rect>8,7,17,14</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/map_anim1.png</key>
            <key type="filename">sprites/map_anim2.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>6,5,13,10</rect>
                <key>scale9Paddings</key>
                <rect>6,5,13,10</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/map_anim3.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>6,4,12,8</rect>
                <key>scale9Paddings</key>
                <rect>6,4,12,8</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/map_anim4.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>7,2,13,5</rect>
                <key>scale9Paddings</key>
                <rect>7,2,13,5</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/map_anim5.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>4,2,8,4</rect>
                <key>scale9Paddings</key>
                <rect>4,2,8,4</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/map_on_copytron_lid_up.png</key>
            <key type="filename">sprites/map_on_copytron_lit_lid_up.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>12,3,25,7</rect>
                <key>scale9Paddings</key>
                <rect>12,3,25,7</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/mid_paper_stack.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>37,19,73,37</rect>
                <key>scale9Paddings</key>
                <rect>37,19,73,37</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/near_paper_stack.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>42,15,84,29</rect>
                <key>scale9Paddings</key>
                <rect>42,15,84,29</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/radiotron.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>10,11,20,23</rect>
                <key>scale9Paddings</key>
                <rect>10,11,20,23</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/radiotron_light_off.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>1,0,1,1</rect>
                <key>scale9Paddings</key>
                <rect>1,0,1,1</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/radiotron_light_on.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>1,1,2,1</rect>
                <key>scale9Paddings</key>
                <rect>1,1,2,1</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/sky.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>85,29,170,57</rect>
                <key>scale9Paddings</key>
                <rect>85,29,170,57</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/tray_copy.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>8,1,15,3</rect>
                <key>scale9Paddings</key>
                <rect>8,1,15,3</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/tray_copy_mask.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>9,5,17,9</rect>
                <key>scale9Paddings</key>
                <rect>9,5,17,9</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/typewriter.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>9,5,19,9</rect>
                <key>scale9Paddings</key>
                <rect>9,5,19,9</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
            <key type="filename">sprites/typewriter_paper.png</key>
            <struct type="IndividualSpriteSettings">
                <key>pivotPoint</key>
                <point_f>0.5,0.5</point_f>
                <key>spriteScale</key>
                <double>1</double>
                <key>scale9Enabled</key>
                <false/>
                <key>scale9Borders</key>
                <rect>6,4,11,8</rect>
                <key>scale9Paddings</key>
                <rect>6,4,11,8</rect>
                <key>scale9FromFile</key>
                <false/>
            </struct>
        </map>
        <key>fileList</key>
        <array>
            <filename>sprites</filename>
        </array>
        <key>ignoreFileList</key>
        <array/>
        <key>replaceList</key>
        <array/>
        <key>ignoredWarnings</key>
        <array/>
        <key>commonDivisorX</key>
        <uint>1</uint>
        <key>commonDivisorY</key>
        <uint>1</uint>
        <key>packNormalMaps</key>
        <false/>
        <key>autodetectNormalMaps</key>
        <true/>
        <key>normalMapFilter</key>
        <string></string>
        <key>normalMapSuffix</key>
        <string></string>
        <key>normalMapSheetFileName</key>
        <filename></filename>
        <key>exporterProperties</key>
        <map type="ExporterProperties"/>
    </struct>
</data>
