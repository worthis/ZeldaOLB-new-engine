CXX = arm-linux-gnueabihf-g++
CFLAGS = -O2 -Wall
CXXFLAGS = -I/opt/miyoomini-toolchain/arm-linux-gnueabihf/libc/usr/include -ISDL
LDFLAGS = -L/opt/miyoomini-toolchain/arm-linux-gnueabihf/libc/usr/lib -LSDL/libs -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_rotozoom
OBJECTS = src/config/AudioHelper.o src/config/ConfigurationManager.o src/config/TextHelper.o src/engine/audio/AudioConfiguration.o src/engine/audio/AudioManager.o src/engine/renderer/CircularTransition.o src/engine/renderer/SimpleTransition.o src/engine/resources/ResourceManager.o src/engine/resources/WFile.o src/engine/resources/WImage.o src/engine/resources/WMusic.o src/engine/resources/WResource.o src/engine/resources/WSound.o src/engine/texts/Text.o src/engine/texts/TextConfiguration.o src/engine/texts/TextManager.o src/engine/util/geometry/BoundingBox.o src/engine/util/list/List.o src/engine/util/list/Listable.o src/engine/util/list/ListCell.o src/engine/util/physic/SlideManager.o src/engine/util/time/Chrono.o src/engine/util/time/Metronome.o src/engine/util/tree/Node.o src/engine/util/tree/Quadtree.o src/engine/window/Event.o src/engine/window/Timer.o src/engine/window/WindowManager.o src/game/algo/AStar.o src/game/content/effects/Debris.o src/game/content/effects/Feuilles.o src/game/content/effects/Flamme.o src/game/content/effects/FumeeBlanche.o src/game/content/effects/FumeeRose.o src/game/content/effects/FumeeViolette.o src/game/content/effects/Plouf.o src/game/content/effects/Splash.o src/game/content/ennemis/Ennemi001.o src/game/content/ennemis/Ennemi002.o src/game/content/ennemis/Ennemi003.o src/game/content/ennemis/Ennemi004.o src/game/content/ennemis/Ennemi005.o src/game/content/ennemis/Ennemi006.o src/game/content/ennemis/Ennemi007.o src/game/content/ennemis/Ennemi008.o src/game/content/ennemis/Ennemi009.o src/game/content/ennemis/Ennemi010.o src/game/content/ennemis/Ennemi011.o src/game/content/ennemis/Ennemi012.o src/game/content/ennemis/Ennemi013.o src/game/content/ennemis/Ennemi014.o src/game/content/ennemis/Ennemi015.o src/game/content/ennemis/Ennemi016.o src/game/content/ennemis/Ennemi018.o src/game/content/ennemis/Ennemi019.o src/game/content/ennemis/Ennemi021.o src/game/content/ennemis/Ennemi022.o src/game/content/ennemis/Ennemi023.o src/game/content/ennemis/Ennemi024.o src/game/content/ennemis/Ennemi025.o src/game/content/ennemis/Ennemi026.o src/game/content/ennemis/Ennemi027.o src/game/content/ennemis/Ennemi028.o src/game/content/ennemis/Ennemi029.o src/game/content/ennemis/Ennemi030.o src/game/content/ennemis/Ennemi031.o src/game/content/ennemis/Ennemi032.o src/game/content/ennemis/Ennemi033.o src/game/content/ennemis/Ennemi034.o src/game/content/ennemis/Ennemi035.o src/game/content/ennemis/Ennemi037.o src/game/content/ennemis/Ennemi038.o src/game/content/ennemis/Ennemi039.o src/game/content/ennemis/Ennemi040.o src/game/content/ennemis/Ennemi041.o src/game/content/ennemis/Ennemi042.o src/game/content/ennemis/Ennemi043.o src/game/content/ennemis/Ennemi044.o src/game/content/ennemis/Ennemi045.o src/game/content/ennemis/Ennemi046.o src/game/content/ennemis/Ennemi047.o src/game/content/ennemis/Ennemi048.o src/game/content/ennemis/Ennemi050.o src/game/content/ennemis/Ennemi052.o src/game/content/ennemis/Ennemi053.o src/game/content/ennemis/Ennemi054.o src/game/content/ennemis/Ennemi055.o src/game/content/ennemis/Ennemi056.o src/game/content/ennemis/Ennemi057.o src/game/content/ennemis/Ennemi058.o src/game/content/ennemis/Ennemi060.o src/game/content/ennemis/Ennemi062.o src/game/content/ennemis/Ennemi063.o src/game/content/ennemis/Ennemi064.o src/game/content/ennemis/Ennemi066.o src/game/content/ennemis/Ennemi068.o src/game/content/ennemis/Ennemi069.o src/game/content/ennemis/Ennemi071.o src/game/content/ennemis/Ennemi072.o src/game/content/ennemis/Ennemi073.o src/game/content/ennemis/Ennemi074.o src/game/content/ennemis/Ennemi075.o src/game/content/ennemis/Ennemi076.o src/game/content/helper/ItemHelper.o src/game/content/helper/ItemRandomizer.o src/game/content/helper/MapHelper.o src/game/content/helper/ProjectileHelper.o src/game/content/items/Arrow.o src/game/content/items/Bomb.o src/game/content/items/Coeur.o src/game/content/items/Graal.o src/game/content/items/MagieGrand.o src/game/content/items/MagiePetit.o src/game/content/items/PetitCoeur.o src/game/content/items/PetiteCle.o src/game/content/items/QuartCoeur.o src/game/content/items/RubisBleu.o src/game/content/items/RubisRouge.o src/game/content/items/RubisVert.o src/game/content/items/Triforce.o src/game/content/link/Inventory.o src/game/content/link/Link.o src/game/content/link/Shield.o src/game/content/link/Status.o src/game/content/link/Sword.o src/game/content/objects/Barriere.o src/game/content/objects/Caisse.o src/game/content/objects/Coffre.o src/game/content/objects/Interrupteur.o src/game/content/objects/InterrupteurStar.o src/game/content/objects/Jarre.o src/game/content/objects/ObjBomb.o src/game/content/objects/Pancarte.o src/game/content/objects/PiegeColere.o src/game/content/objects/PiegeDemi.o src/game/content/objects/PiegeFeu.o src/game/content/objects/PiegeLong.o src/game/content/objects/PiegeMain.o src/game/content/objects/PiegeMurs.o src/game/content/objects/PiegePics.o src/game/content/objects/Pierre.o src/game/content/objects/Pnj.o src/game/content/objects/Poule.o src/game/content/objects/Sphere.o src/game/content/objects/Stele.o src/game/content/objects/TalkableArea.o src/game/content/projectiles/ProjArcMagique.o src/game/content/projectiles/ProjArrow.o src/game/content/projectiles/ProjBaguetteFeu.o src/game/content/projectiles/ProjBaguetteGlace.o src/game/content/projectiles/ProjBigFeu.o src/game/content/projectiles/ProjBigGlace.o src/game/content/projectiles/ProjBouleColere.o src/game/content/projectiles/ProjBouleDemi.o src/game/content/projectiles/ProjBouleFeu.o src/game/content/projectiles/ProjBouleMort.o src/game/content/projectiles/ProjBoulet.o src/game/content/projectiles/ProjEclair.o src/game/content/projectiles/ProjFeuLong.o src/game/content/projectiles/ProjGrappin.o src/game/content/projectiles/ProjLapin.o src/game/content/projectiles/ProjUltime.o src/game/content/scene/AnimationInGame.o src/game/content/scene/Camera.o src/game/content/scene/Hud.o src/game/content/scene/Map.o src/game/content/scene/MapInitializer.o src/game/content/types/Collisionable.o src/game/content/types/Drawable.o src/game/content/types/Effect.o src/game/content/types/Ennemi.o src/game/content/types/Item.o src/game/content/types/Loopable.o src/game/content/types/Object.o src/game/content/types/Portable.o src/game/content/types/Poussable.o src/game/content/types/Projectile.o src/game/ending/credits/Credits.o src/game/ending/credits/CreditsController.o src/game/ending/EndingController.o src/game/ending/final/Final.o src/game/ending/final/FinalController.o src/game/ending/score/Score.o src/game/ending/score/ScoreController.o src/game/ending/story/StoryController.o src/game/ending/story/StoryTextArea.o src/game/game/GameController.o src/game/game/help/Help.o src/game/game/help/HelpController.o src/game/game/map/MapController.o src/game/game/map/MapDonjon.o src/game/game/map/MapOcarina.o src/game/game/map/MapOverworld.o src/game/game/menu/GameMenuController.o src/game/game/menu/Menu.o src/game/game/monsters/Monsters.o src/game/game/monsters/MonstersController.o src/game/game/ocarina/Ocarina.o src/game/game/ocarina/OcarinaController.o src/game/game/scene/Scene.o src/game/game/scene/SceneController.o src/game/game/teleport/Teleport.o src/game/game/teleport/TeleportController.o src/game/game/textes/TextArea.o src/game/game/textes/TextController.o src/game/game/transitionMaps/TransitionMaps.o src/game/game/transitionMaps/TransitionMapsController.o src/game/game/transitionRooms/TransitionRooms.o src/game/game/transitionRooms/TransitionRoomsController.o src/game/GlobalSave.o src/game/keys/Action.o src/game/keys/JoystickBinder.o src/game/keys/KeyBinder.o src/game/logo/Logo.o src/game/logo/LogoController.o src/game/MainController.o src/game/menu/main/MainMenu.o src/game/menu/main/MainMenuController.o src/game/menu/MenuController.o src/game/menu/options/audio/OptionsAudio.o src/game/menu/options/audio/OptionsAudioController.o src/game/menu/options/commands/joystick/CommandsJoystick.o src/game/menu/options/commands/joystick/CommandsJoystickController.o src/game/menu/options/commands/keyboard/CommandsKeyboard.o src/game/menu/options/commands/keyboard/CommandsKeyboardController.o src/game/menu/options/commands/main/CommandsMain.o src/game/menu/options/commands/main/CommandsMainController.o src/game/menu/options/commands/OptionsCommandsController.o src/game/menu/options/game/OptionsGame.o src/game/menu/options/game/OptionsGameController.o src/game/menu/options/main/OptionsMain.o src/game/menu/options/main/OptionsMainController.o src/game/menu/options/OptionsController.o src/game/menu/records/Records.o src/game/menu/records/RecordsController.o src/game/opening/Opening.o src/game/opening/OpeningController.o src/game/opening/OpeningTextArea.o src/game/Save.o src/game/title/Title.o src/game/title/TitleController.o src/main.o 
OUTPUT = ZeldaOLB


main: $(OBJECTS)
	$(CXX) $(OBJECTS) $(CFLAGS) -o $(OUTPUT) $(LDFLAGS)
AudioHelper.o: AudioHelper.cpp
	$(CXX) $(CFLAGS) -c AudioHelper.cpp
ConfigurationManager.o: ConfigurationManager.cpp
	$(CXX) $(CFLAGS) -c ConfigurationManager.cpp
TextHelper.o: TextHelper.cpp
	$(CXX) $(CFLAGS) -c TextHelper.cpp
AudioConfiguration.o: AudioConfiguration.cpp
	$(CXX) $(CFLAGS) -c AudioConfiguration.cpp
AudioManager.o: AudioManager.cpp
	$(CXX) $(CFLAGS) -c AudioManager.cpp
CircularTransition.o: CircularTransition.cpp
	$(CXX) $(CFLAGS) -c CircularTransition.cpp
SimpleTransition.o: SimpleTransition.cpp
	$(CXX) $(CFLAGS) -c SimpleTransition.cpp
ResourceManager.o: ResourceManager.cpp
	$(CXX) $(CFLAGS) -c ResourceManager.cpp
WFile.o: WFile.cpp
	$(CXX) $(CFLAGS) -c WFile.cpp
WImage.o: WImage.cpp
	$(CXX) $(CFLAGS) -c WImage.cpp
WMusic.o: WMusic.cpp
	$(CXX) $(CFLAGS) -c WMusic.cpp
WResource.o: WResource.cpp
	$(CXX) $(CFLAGS) -c WResource.cpp
WSound.o: WSound.cpp
	$(CXX) $(CFLAGS) -c WSound.cpp
Text.o: Text.cpp
	$(CXX) $(CFLAGS) -c Text.cpp
TextConfiguration.o: TextConfiguration.cpp
	$(CXX) $(CFLAGS) -c TextConfiguration.cpp
TextManager.o: TextManager.cpp
	$(CXX) $(CFLAGS) -c TextManager.cpp
BoundingBox.o: BoundingBox.cpp
	$(CXX) $(CFLAGS) -c BoundingBox.cpp
List.o: List.cpp
	$(CXX) $(CFLAGS) -c List.cpp
Listable.o: Listable.cpp
	$(CXX) $(CFLAGS) -c Listable.cpp
ListCell.o: ListCell.cpp
	$(CXX) $(CFLAGS) -c ListCell.cpp
SlideManager.o: SlideManager.cpp
	$(CXX) $(CFLAGS) -c SlideManager.cpp
Chrono.o: Chrono.cpp
	$(CXX) $(CFLAGS) -c Chrono.cpp
Metronome.o: Metronome.cpp
	$(CXX) $(CFLAGS) -c Metronome.cpp
Node.o: Node.cpp
	$(CXX) $(CFLAGS) -c Node.cpp
Quadtree.o: Quadtree.cpp
	$(CXX) $(CFLAGS) -c Quadtree.cpp
Event.o: Event.cpp
	$(CXX) $(CFLAGS) -c Event.cpp
Timer.o: Timer.cpp
	$(CXX) $(CFLAGS) -c Timer.cpp
WindowManager.o: WindowManager.cpp
	$(CXX) $(CFLAGS) -c WindowManager.cpp
AStar.o: AStar.cpp
	$(CXX) $(CFLAGS) -c AStar.cpp
Debris.o: Debris.cpp
	$(CXX) $(CFLAGS) -c Debris.cpp
Feuilles.o: Feuilles.cpp
	$(CXX) $(CFLAGS) -c Feuilles.cpp
Flamme.o: Flamme.cpp
	$(CXX) $(CFLAGS) -c Flamme.cpp
FumeeBlanche.o: FumeeBlanche.cpp
	$(CXX) $(CFLAGS) -c FumeeBlanche.cpp
FumeeRose.o: FumeeRose.cpp
	$(CXX) $(CFLAGS) -c FumeeRose.cpp
FumeeViolette.o: FumeeViolette.cpp
	$(CXX) $(CFLAGS) -c FumeeViolette.cpp
Plouf.o: Plouf.cpp
	$(CXX) $(CFLAGS) -c Plouf.cpp
Splash.o: Splash.cpp
	$(CXX) $(CFLAGS) -c Splash.cpp
Ennemi001.o: Ennemi001.cpp
	$(CXX) $(CFLAGS) -c Ennemi001.cpp
Ennemi002.o: Ennemi002.cpp
	$(CXX) $(CFLAGS) -c Ennemi002.cpp
Ennemi003.o: Ennemi003.cpp
	$(CXX) $(CFLAGS) -c Ennemi003.cpp
Ennemi004.o: Ennemi004.cpp
	$(CXX) $(CFLAGS) -c Ennemi004.cpp
Ennemi005.o: Ennemi005.cpp
	$(CXX) $(CFLAGS) -c Ennemi005.cpp
Ennemi006.o: Ennemi006.cpp
	$(CXX) $(CFLAGS) -c Ennemi006.cpp
Ennemi007.o: Ennemi007.cpp
	$(CXX) $(CFLAGS) -c Ennemi007.cpp
Ennemi008.o: Ennemi008.cpp
	$(CXX) $(CFLAGS) -c Ennemi008.cpp
Ennemi009.o: Ennemi009.cpp
	$(CXX) $(CFLAGS) -c Ennemi009.cpp
Ennemi010.o: Ennemi010.cpp
	$(CXX) $(CFLAGS) -c Ennemi010.cpp
Ennemi011.o: Ennemi011.cpp
	$(CXX) $(CFLAGS) -c Ennemi011.cpp
Ennemi012.o: Ennemi012.cpp
	$(CXX) $(CFLAGS) -c Ennemi012.cpp
Ennemi013.o: Ennemi013.cpp
	$(CXX) $(CFLAGS) -c Ennemi013.cpp
Ennemi014.o: Ennemi014.cpp
	$(CXX) $(CFLAGS) -c Ennemi014.cpp
Ennemi015.o: Ennemi015.cpp
	$(CXX) $(CFLAGS) -c Ennemi015.cpp
Ennemi016.o: Ennemi016.cpp
	$(CXX) $(CFLAGS) -c Ennemi016.cpp
Ennemi018.o: Ennemi018.cpp
	$(CXX) $(CFLAGS) -c Ennemi018.cpp
Ennemi019.o: Ennemi019.cpp
	$(CXX) $(CFLAGS) -c Ennemi019.cpp
Ennemi021.o: Ennemi021.cpp
	$(CXX) $(CFLAGS) -c Ennemi021.cpp
Ennemi022.o: Ennemi022.cpp
	$(CXX) $(CFLAGS) -c Ennemi022.cpp
Ennemi023.o: Ennemi023.cpp
	$(CXX) $(CFLAGS) -c Ennemi023.cpp
Ennemi024.o: Ennemi024.cpp
	$(CXX) $(CFLAGS) -c Ennemi024.cpp
Ennemi025.o: Ennemi025.cpp
	$(CXX) $(CFLAGS) -c Ennemi025.cpp
Ennemi026.o: Ennemi026.cpp
	$(CXX) $(CFLAGS) -c Ennemi026.cpp
Ennemi027.o: Ennemi027.cpp
	$(CXX) $(CFLAGS) -c Ennemi027.cpp
Ennemi028.o: Ennemi028.cpp
	$(CXX) $(CFLAGS) -c Ennemi028.cpp
Ennemi029.o: Ennemi029.cpp
	$(CXX) $(CFLAGS) -c Ennemi029.cpp
Ennemi030.o: Ennemi030.cpp
	$(CXX) $(CFLAGS) -c Ennemi030.cpp
Ennemi031.o: Ennemi031.cpp
	$(CXX) $(CFLAGS) -c Ennemi031.cpp
Ennemi032.o: Ennemi032.cpp
	$(CXX) $(CFLAGS) -c Ennemi032.cpp
Ennemi033.o: Ennemi033.cpp
	$(CXX) $(CFLAGS) -c Ennemi033.cpp
Ennemi034.o: Ennemi034.cpp
	$(CXX) $(CFLAGS) -c Ennemi034.cpp
Ennemi035.o: Ennemi035.cpp
	$(CXX) $(CFLAGS) -c Ennemi035.cpp
Ennemi037.o: Ennemi037.cpp
	$(CXX) $(CFLAGS) -c Ennemi037.cpp
Ennemi038.o: Ennemi038.cpp
	$(CXX) $(CFLAGS) -c Ennemi038.cpp
Ennemi039.o: Ennemi039.cpp
	$(CXX) $(CFLAGS) -c Ennemi039.cpp
Ennemi040.o: Ennemi040.cpp
	$(CXX) $(CFLAGS) -c Ennemi040.cpp
Ennemi041.o: Ennemi041.cpp
	$(CXX) $(CFLAGS) -c Ennemi041.cpp
Ennemi042.o: Ennemi042.cpp
	$(CXX) $(CFLAGS) -c Ennemi042.cpp
Ennemi043.o: Ennemi043.cpp
	$(CXX) $(CFLAGS) -c Ennemi043.cpp
Ennemi044.o: Ennemi044.cpp
	$(CXX) $(CFLAGS) -c Ennemi044.cpp
Ennemi045.o: Ennemi045.cpp
	$(CXX) $(CFLAGS) -c Ennemi045.cpp
Ennemi046.o: Ennemi046.cpp
	$(CXX) $(CFLAGS) -c Ennemi046.cpp
Ennemi047.o: Ennemi047.cpp
	$(CXX) $(CFLAGS) -c Ennemi047.cpp
Ennemi048.o: Ennemi048.cpp
	$(CXX) $(CFLAGS) -c Ennemi048.cpp
Ennemi050.o: Ennemi050.cpp
	$(CXX) $(CFLAGS) -c Ennemi050.cpp
Ennemi052.o: Ennemi052.cpp
	$(CXX) $(CFLAGS) -c Ennemi052.cpp
Ennemi053.o: Ennemi053.cpp
	$(CXX) $(CFLAGS) -c Ennemi053.cpp
Ennemi054.o: Ennemi054.cpp
	$(CXX) $(CFLAGS) -c Ennemi054.cpp
Ennemi055.o: Ennemi055.cpp
	$(CXX) $(CFLAGS) -c Ennemi055.cpp
Ennemi056.o: Ennemi056.cpp
	$(CXX) $(CFLAGS) -c Ennemi056.cpp
Ennemi057.o: Ennemi057.cpp
	$(CXX) $(CFLAGS) -c Ennemi057.cpp
Ennemi058.o: Ennemi058.cpp
	$(CXX) $(CFLAGS) -c Ennemi058.cpp
Ennemi060.o: Ennemi060.cpp
	$(CXX) $(CFLAGS) -c Ennemi060.cpp
Ennemi062.o: Ennemi062.cpp
	$(CXX) $(CFLAGS) -c Ennemi062.cpp
Ennemi063.o: Ennemi063.cpp
	$(CXX) $(CFLAGS) -c Ennemi063.cpp
Ennemi064.o: Ennemi064.cpp
	$(CXX) $(CFLAGS) -c Ennemi064.cpp
Ennemi066.o: Ennemi066.cpp
	$(CXX) $(CFLAGS) -c Ennemi066.cpp
Ennemi068.o: Ennemi068.cpp
	$(CXX) $(CFLAGS) -c Ennemi068.cpp
Ennemi069.o: Ennemi069.cpp
	$(CXX) $(CFLAGS) -c Ennemi069.cpp
Ennemi071.o: Ennemi071.cpp
	$(CXX) $(CFLAGS) -c Ennemi071.cpp
Ennemi072.o: Ennemi072.cpp
	$(CXX) $(CFLAGS) -c Ennemi072.cpp
Ennemi073.o: Ennemi073.cpp
	$(CXX) $(CFLAGS) -c Ennemi073.cpp
Ennemi074.o: Ennemi074.cpp
	$(CXX) $(CFLAGS) -c Ennemi074.cpp
Ennemi075.o: Ennemi075.cpp
	$(CXX) $(CFLAGS) -c Ennemi075.cpp
Ennemi076.o: Ennemi076.cpp
	$(CXX) $(CFLAGS) -c Ennemi076.cpp
ItemHelper.o: ItemHelper.cpp
	$(CXX) $(CFLAGS) -c ItemHelper.cpp
ItemRandomizer.o: ItemRandomizer.cpp
	$(CXX) $(CFLAGS) -c ItemRandomizer.cpp
MapHelper.o: MapHelper.cpp
	$(CXX) $(CFLAGS) -c MapHelper.cpp
ProjectileHelper.o: ProjectileHelper.cpp
	$(CXX) $(CFLAGS) -c ProjectileHelper.cpp
Arrow.o: Arrow.cpp
	$(CXX) $(CFLAGS) -c Arrow.cpp
Bomb.o: Bomb.cpp
	$(CXX) $(CFLAGS) -c Bomb.cpp
Coeur.o: Coeur.cpp
	$(CXX) $(CFLAGS) -c Coeur.cpp
Graal.o: Graal.cpp
	$(CXX) $(CFLAGS) -c Graal.cpp
MagieGrand.o: MagieGrand.cpp
	$(CXX) $(CFLAGS) -c MagieGrand.cpp
MagiePetit.o: MagiePetit.cpp
	$(CXX) $(CFLAGS) -c MagiePetit.cpp
PetitCoeur.o: PetitCoeur.cpp
	$(CXX) $(CFLAGS) -c PetitCoeur.cpp
PetiteCle.o: PetiteCle.cpp
	$(CXX) $(CFLAGS) -c PetiteCle.cpp
QuartCoeur.o: QuartCoeur.cpp
	$(CXX) $(CFLAGS) -c QuartCoeur.cpp
RubisBleu.o: RubisBleu.cpp
	$(CXX) $(CFLAGS) -c RubisBleu.cpp
RubisRouge.o: RubisRouge.cpp
	$(CXX) $(CFLAGS) -c RubisRouge.cpp
RubisVert.o: RubisVert.cpp
	$(CXX) $(CFLAGS) -c RubisVert.cpp
Triforce.o: Triforce.cpp
	$(CXX) $(CFLAGS) -c Triforce.cpp
Inventory.o: Inventory.cpp
	$(CXX) $(CFLAGS) -c Inventory.cpp
Link.o: Link.cpp
	$(CXX) $(CFLAGS) -c Link.cpp
Shield.o: Shield.cpp
	$(CXX) $(CFLAGS) -c Shield.cpp
Status.o: Status.cpp
	$(CXX) $(CFLAGS) -c Status.cpp
Sword.o: Sword.cpp
	$(CXX) $(CFLAGS) -c Sword.cpp
Barriere.o: Barriere.cpp
	$(CXX) $(CFLAGS) -c Barriere.cpp
Caisse.o: Caisse.cpp
	$(CXX) $(CFLAGS) -c Caisse.cpp
Coffre.o: Coffre.cpp
	$(CXX) $(CFLAGS) -c Coffre.cpp
Interrupteur.o: Interrupteur.cpp
	$(CXX) $(CFLAGS) -c Interrupteur.cpp
InterrupteurStar.o: InterrupteurStar.cpp
	$(CXX) $(CFLAGS) -c InterrupteurStar.cpp
Jarre.o: Jarre.cpp
	$(CXX) $(CFLAGS) -c Jarre.cpp
ObjBomb.o: ObjBomb.cpp
	$(CXX) $(CFLAGS) -c ObjBomb.cpp
Pancarte.o: Pancarte.cpp
	$(CXX) $(CFLAGS) -c Pancarte.cpp
PiegeColere.o: PiegeColere.cpp
	$(CXX) $(CFLAGS) -c PiegeColere.cpp
PiegeDemi.o: PiegeDemi.cpp
	$(CXX) $(CFLAGS) -c PiegeDemi.cpp
PiegeFeu.o: PiegeFeu.cpp
	$(CXX) $(CFLAGS) -c PiegeFeu.cpp
PiegeLong.o: PiegeLong.cpp
	$(CXX) $(CFLAGS) -c PiegeLong.cpp
PiegeMain.o: PiegeMain.cpp
	$(CXX) $(CFLAGS) -c PiegeMain.cpp
PiegeMurs.o: PiegeMurs.cpp
	$(CXX) $(CFLAGS) -c PiegeMurs.cpp
PiegePics.o: PiegePics.cpp
	$(CXX) $(CFLAGS) -c PiegePics.cpp
Pierre.o: Pierre.cpp
	$(CXX) $(CFLAGS) -c Pierre.cpp
Pnj.o: Pnj.cpp
	$(CXX) $(CFLAGS) -c Pnj.cpp
Poule.o: Poule.cpp
	$(CXX) $(CFLAGS) -c Poule.cpp
Sphere.o: Sphere.cpp
	$(CXX) $(CFLAGS) -c Sphere.cpp
Stele.o: Stele.cpp
	$(CXX) $(CFLAGS) -c Stele.cpp
TalkableArea.o: TalkableArea.cpp
	$(CXX) $(CFLAGS) -c TalkableArea.cpp
ProjArcMagique.o: ProjArcMagique.cpp
	$(CXX) $(CFLAGS) -c ProjArcMagique.cpp
ProjArrow.o: ProjArrow.cpp
	$(CXX) $(CFLAGS) -c ProjArrow.cpp
ProjBaguetteFeu.o: ProjBaguetteFeu.cpp
	$(CXX) $(CFLAGS) -c ProjBaguetteFeu.cpp
ProjBaguetteGlace.o: ProjBaguetteGlace.cpp
	$(CXX) $(CFLAGS) -c ProjBaguetteGlace.cpp
ProjBigFeu.o: ProjBigFeu.cpp
	$(CXX) $(CFLAGS) -c ProjBigFeu.cpp
ProjBigGlace.o: ProjBigGlace.cpp
	$(CXX) $(CFLAGS) -c ProjBigGlace.cpp
ProjBouleColere.o: ProjBouleColere.cpp
	$(CXX) $(CFLAGS) -c ProjBouleColere.cpp
ProjBouleDemi.o: ProjBouleDemi.cpp
	$(CXX) $(CFLAGS) -c ProjBouleDemi.cpp
ProjBouleFeu.o: ProjBouleFeu.cpp
	$(CXX) $(CFLAGS) -c ProjBouleFeu.cpp
ProjBouleMort.o: ProjBouleMort.cpp
	$(CXX) $(CFLAGS) -c ProjBouleMort.cpp
ProjBoulet.o: ProjBoulet.cpp
	$(CXX) $(CFLAGS) -c ProjBoulet.cpp
ProjEclair.o: ProjEclair.cpp
	$(CXX) $(CFLAGS) -c ProjEclair.cpp
ProjFeuLong.o: ProjFeuLong.cpp
	$(CXX) $(CFLAGS) -c ProjFeuLong.cpp
ProjGrappin.o: ProjGrappin.cpp
	$(CXX) $(CFLAGS) -c ProjGrappin.cpp
ProjLapin.o: ProjLapin.cpp
	$(CXX) $(CFLAGS) -c ProjLapin.cpp
ProjUltime.o: ProjUltime.cpp
	$(CXX) $(CFLAGS) -c ProjUltime.cpp
AnimationInGame.o: AnimationInGame.cpp
	$(CXX) $(CFLAGS) -c AnimationInGame.cpp
Camera.o: Camera.cpp
	$(CXX) $(CFLAGS) -c Camera.cpp
Hud.o: Hud.cpp
	$(CXX) $(CFLAGS) -c Hud.cpp
Map.o: Map.cpp
	$(CXX) $(CFLAGS) -c Map.cpp
MapInitializer.o: MapInitializer.cpp
	$(CXX) $(CFLAGS) -c MapInitializer.cpp
Collisionable.o: Collisionable.cpp
	$(CXX) $(CFLAGS) -c Collisionable.cpp
Drawable.o: Drawable.cpp
	$(CXX) $(CFLAGS) -c Drawable.cpp
Effect.o: Effect.cpp
	$(CXX) $(CFLAGS) -c Effect.cpp
Ennemi.o: Ennemi.cpp
	$(CXX) $(CFLAGS) -c Ennemi.cpp
Item.o: Item.cpp
	$(CXX) $(CFLAGS) -c Item.cpp
Loopable.o: Loopable.cpp
	$(CXX) $(CFLAGS) -c Loopable.cpp
Object.o: Object.cpp
	$(CXX) $(CFLAGS) -c Object.cpp
Portable.o: Portable.cpp
	$(CXX) $(CFLAGS) -c Portable.cpp
Poussable.o: Poussable.cpp
	$(CXX) $(CFLAGS) -c Poussable.cpp
Projectile.o: Projectile.cpp
	$(CXX) $(CFLAGS) -c Projectile.cpp
Credits.o: Credits.cpp
	$(CXX) $(CFLAGS) -c Credits.cpp
CreditsController.o: CreditsController.cpp
	$(CXX) $(CFLAGS) -c CreditsController.cpp
EndingController.o: EndingController.cpp
	$(CXX) $(CFLAGS) -c EndingController.cpp
Final.o: Final.cpp
	$(CXX) $(CFLAGS) -c Final.cpp
FinalController.o: FinalController.cpp
	$(CXX) $(CFLAGS) -c FinalController.cpp
Score.o: Score.cpp
	$(CXX) $(CFLAGS) -c Score.cpp
ScoreController.o: ScoreController.cpp
	$(CXX) $(CFLAGS) -c ScoreController.cpp
StoryController.o: StoryController.cpp
	$(CXX) $(CFLAGS) -c StoryController.cpp
StoryTextArea.o: StoryTextArea.cpp
	$(CXX) $(CFLAGS) -c StoryTextArea.cpp
GameController.o: GameController.cpp
	$(CXX) $(CFLAGS) -c GameController.cpp
Help.o: Help.cpp
	$(CXX) $(CFLAGS) -c Help.cpp
HelpController.o: HelpController.cpp
	$(CXX) $(CFLAGS) -c HelpController.cpp
MapController.o: MapController.cpp
	$(CXX) $(CFLAGS) -c MapController.cpp
MapDonjon.o: MapDonjon.cpp
	$(CXX) $(CFLAGS) -c MapDonjon.cpp
MapOcarina.o: MapOcarina.cpp
	$(CXX) $(CFLAGS) -c MapOcarina.cpp
MapOverworld.o: MapOverworld.cpp
	$(CXX) $(CFLAGS) -c MapOverworld.cpp
GameMenuController.o: GameMenuController.cpp
	$(CXX) $(CFLAGS) -c GameMenuController.cpp
Menu.o: Menu.cpp
	$(CXX) $(CFLAGS) -c Menu.cpp
Monsters.o: Monsters.cpp
	$(CXX) $(CFLAGS) -c Monsters.cpp
MonstersController.o: MonstersController.cpp
	$(CXX) $(CFLAGS) -c MonstersController.cpp
Ocarina.o: Ocarina.cpp
	$(CXX) $(CFLAGS) -c Ocarina.cpp
OcarinaController.o: OcarinaController.cpp
	$(CXX) $(CFLAGS) -c OcarinaController.cpp
Scene.o: Scene.cpp
	$(CXX) $(CFLAGS) -c Scene.cpp
SceneController.o: SceneController.cpp
	$(CXX) $(CFLAGS) -c SceneController.cpp
Teleport.o: Teleport.cpp
	$(CXX) $(CFLAGS) -c Teleport.cpp
TeleportController.o: TeleportController.cpp
	$(CXX) $(CFLAGS) -c TeleportController.cpp
TextArea.o: TextArea.cpp
	$(CXX) $(CFLAGS) -c TextArea.cpp
TextController.o: TextController.cpp
	$(CXX) $(CFLAGS) -c TextController.cpp
TransitionMaps.o: TransitionMaps.cpp
	$(CXX) $(CFLAGS) -c TransitionMaps.cpp
TransitionMapsController.o: TransitionMapsController.cpp
	$(CXX) $(CFLAGS) -c TransitionMapsController.cpp
TransitionRooms.o: TransitionRooms.cpp
	$(CXX) $(CFLAGS) -c TransitionRooms.cpp
TransitionRoomsController.o: TransitionRoomsController.cpp
	$(CXX) $(CFLAGS) -c TransitionRoomsController.cpp
GlobalSave.o: GlobalSave.cpp
	$(CXX) $(CFLAGS) -c GlobalSave.cpp
Action.o: Action.cpp
	$(CXX) $(CFLAGS) -c Action.cpp
JoystickBinder.o: JoystickBinder.cpp
	$(CXX) $(CFLAGS) -c JoystickBinder.cpp
KeyBinder.o: KeyBinder.cpp
	$(CXX) $(CFLAGS) -c KeyBinder.cpp
Logo.o: Logo.cpp
	$(CXX) $(CFLAGS) -c Logo.cpp
LogoController.o: LogoController.cpp
	$(CXX) $(CFLAGS) -c LogoController.cpp
MainController.o: MainController.cpp
	$(CXX) $(CFLAGS) -c MainController.cpp
MainMenu.o: MainMenu.cpp
	$(CXX) $(CFLAGS) -c MainMenu.cpp
MainMenuController.o: MainMenuController.cpp
	$(CXX) $(CFLAGS) -c MainMenuController.cpp
MenuController.o: MenuController.cpp
	$(CXX) $(CFLAGS) -c MenuController.cpp
OptionsAudio.o: OptionsAudio.cpp
	$(CXX) $(CFLAGS) -c OptionsAudio.cpp
OptionsAudioController.o: OptionsAudioController.cpp
	$(CXX) $(CFLAGS) -c OptionsAudioController.cpp
CommandsJoystick.o: CommandsJoystick.cpp
	$(CXX) $(CFLAGS) -c CommandsJoystick.cpp
CommandsJoystickController.o: CommandsJoystickController.cpp
	$(CXX) $(CFLAGS) -c CommandsJoystickController.cpp
CommandsKeyboard.o: CommandsKeyboard.cpp
	$(CXX) $(CFLAGS) -c CommandsKeyboard.cpp
CommandsKeyboardController.o: CommandsKeyboardController.cpp
	$(CXX) $(CFLAGS) -c CommandsKeyboardController.cpp
CommandsMain.o: CommandsMain.cpp
	$(CXX) $(CFLAGS) -c CommandsMain.cpp
CommandsMainController.o: CommandsMainController.cpp
	$(CXX) $(CFLAGS) -c CommandsMainController.cpp
OptionsCommandsController.o: OptionsCommandsController.cpp
	$(CXX) $(CFLAGS) -c OptionsCommandsController.cpp
OptionsGame.o: OptionsGame.cpp
	$(CXX) $(CFLAGS) -c OptionsGame.cpp
OptionsGameController.o: OptionsGameController.cpp
	$(CXX) $(CFLAGS) -c OptionsGameController.cpp
OptionsMain.o: OptionsMain.cpp
	$(CXX) $(CFLAGS) -c OptionsMain.cpp
OptionsMainController.o: OptionsMainController.cpp
	$(CXX) $(CFLAGS) -c OptionsMainController.cpp
OptionsController.o: OptionsController.cpp
	$(CXX) $(CFLAGS) -c OptionsController.cpp
Records.o: Records.cpp
	$(CXX) $(CFLAGS) -c Records.cpp
RecordsController.o: RecordsController.cpp
	$(CXX) $(CFLAGS) -c RecordsController.cpp
Opening.o: Opening.cpp
	$(CXX) $(CFLAGS) -c Opening.cpp
OpeningController.o: OpeningController.cpp
	$(CXX) $(CFLAGS) -c OpeningController.cpp
OpeningTextArea.o: OpeningTextArea.cpp
	$(CXX) $(CFLAGS) -c OpeningTextArea.cpp
Save.o: Save.cpp
	$(CXX) $(CFLAGS) -c Save.cpp
Title.o: Title.cpp
	$(CXX) $(CFLAGS) -c Title.cpp
TitleController.o: TitleController.cpp
	$(CXX) $(CFLAGS) -c TitleController.cpp
main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp


.PHONY : clean

clean :
	-rm -f $(OBJECTS) $(OUTPUT)