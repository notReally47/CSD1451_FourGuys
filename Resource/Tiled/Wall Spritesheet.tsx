<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.9" tiledversion="1.9.2" name="Wall Spritesheet" tilewidth="256" tileheight="288" tilecount="9" columns="9">
 <image source="../Textures/wall.png" width="2304" height="288"/>
 <tile id="0" class="WALL">
  <objectgroup draworder="index" id="3">
   <object id="2" x="35.125" y="93">
    <polygon points="0,0 130.625,-62.125 216.625,-19.375 92.3295,43"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="1" class="WALL">
  <properties>
   <property name="SAVEPOINT" type="bool" value="false"/>
  </properties>
 </tile>
 <tile id="2" class="WALL"/>
 <tile id="3" class="WALL"/>
 <tile id="4" class="WALL"/>
 <tile id="5" class="WALL"/>
 <tile id="6" class="WALL"/>
 <tile id="7" class="WALL">
  <properties>
   <property name="SAVEPOINT" type="bool" value="false"/>
  </properties>
 </tile>
 <tile id="8" class="WALL">
  <objectgroup draworder="index" id="2">
   <object id="1" x="217.375" y="95.625">
    <polygon points="0,0 -122.5,-66.5 -212.25,-22 -86.2841,41.8295"/>
   </object>
  </objectgroup>
 </tile>
</tileset>
