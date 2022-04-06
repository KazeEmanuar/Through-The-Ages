// Parameters: dialog enum ID, (unused), lines per box, left offset, width
//dialog.h
//dialogs.h

#ifdef VERSION_EU
#define COMRADES "friends"
#define PLASTERED "splattered"
#define SCAM_ME "cheat!\n"
#define SCRAM "get lost"
#define YOU_CANT_SWIM_IN_IT "Its too heavy to swim\nwith."
#define GIVE_UP "give up"
#else
#define COMRADES "comrades"
#define PLASTERED "plastered"
#define SCAM_ME "scam\nME. "
#define SCRAM "scram--"
#define YOU_CANT_SWIM_IN_IT "You can't swim in it."
#define GIVE_UP "give"
#endif

//dolphin
DEFINE_DIALOG(DIALOG_000, 1, 3, 30, 200, _("\
You are a lifesaver!\n\
I'll tell all the other\n\
dolphins about this!"))

DEFINE_DIALOG(DIALOG_001, 1, 4, 95, 200, _("\
Hey you!\n\
Luigi and Wario were\n\
looking for you.\n\
They are atop the olymp.\n\
Something about Zeus...\n\
Go there quick!"))
//wiggler alice
DEFINE_DIALOG(DIALOG_002, 1, 3, 95, 200, _("\
Hey, you!\n\
\n\
\n\
I saw you being all tiny.\n\
My tummy has been buzzing\n\
all day!\n\
Could you hop into\n\
my mouth and check\n\
my plumbing?"))
//pink bob omb tutorial guy no pokemon
DEFINE_DIALOG(DIALOG_003, 1, 4, 95, 200, _("\
Hmm...\n\
Come back to me,\n\
when you've found\n\
a partner, buddy."))
//pink bob omb tutorial guy choose one
DEFINE_DIALOG(DIALOG_004, 1, 4, 95, 200, _("\
Hey buddy!\n\
I see you've got a partner!\n\
I'll have you train in\n\
a special course.\n\
Which partner would you\n\
like to train with?"))

//pink bob omb tutorial guy prewarp
DEFINE_DIALOG(DIALOG_005, 1, 1, 30, 200, _("\
Off you go!"))

DEFINE_DIALOG(DIALOG_006, 1, 3, 30, 200, _("\
Hey!!! Don't try to " SCAM_ME
"You've gotta run\n\
the whole course.\n\
Later. Look me up when\n\
you want to race for\n\
real."))

DEFINE_DIALOG(DIALOG_007, 1, 5, 30, 200, _("\
Hufff...fff...pufff...\n\
Whoa! You...really...are...\n\
fast! A human blur!\n\
Here you go--you've won\n\
it, fair and square!"))

//dolphin
DEFINE_DIALOG(DIALOG_008, 1, 4, 30, 200, _("\
I'm stranded!\n\
Please, grab my tail\n\
and drag me back\n\
in the water!"))

DEFINE_DIALOG(DIALOG_009, 1, 5, 30, 200, _("\
Long time, no see! Wow,\n\
have you gotten fast!\n\
Have you been training\n\
on the sly, or is it the\n\
power of the Stars?\n\
I've been feeling down\n\
about losing the last\n\
race. This is my home\n\
course--how about a\n\
rematch?\n\
The goal is in\n\
Windswept Valley.\n\
Ready?\n\
\n\
//Go//// Don't Go"))

DEFINE_DIALOG(DIALOG_010, 1, 4, 30, 200, _("\
You've stepped on the\n\
Wing Cap Switch. Wearing\n\
the Wing Cap, you can\n\
soar through the sky.\n\
Now Wing Caps will pop\n\
out of all the red blocks\n\
you find.\n\
\n\
Would you like to Save?\n\
\n\
//Yes////No"))

DEFINE_DIALOG(DIALOG_011, 1, 4, 30, 200, _("\
You've just stepped on\n\
the Metal Cap Switch!\n\
The Metal Cap makes\n\
Mario invincible.\n\
Now Metal Caps will\n\
pop out of all of the\n\
green blocks you find.\n\
\n\
Would you like to Save?\n\
\n\
//Yes////No"))

DEFINE_DIALOG(DIALOG_012, 1, 4, 30, 200, _("\
You've just stepped on\n\
the Vanish Cap Switch.\n\
The Vanish Cap makes\n\
Mario disappear.\n\
Now Vanish Caps will pop\n\
from all of the blue\n\
blocks you find.\n\
\n\
Would you like to Save?\n\
\n\
//Yes////No"))

DEFINE_DIALOG(DIALOG_013, 1, 4, 30, 200, _("\
You've collected 100\n\
coins!\n\
Do you want to Save?\n\
//Yes////No"))

DEFINE_DIALOG(DIALOG_014, 1, 4, 30, 200, _("\
Wow! Another Power Star!\n\
Mario gains more courage\n\
from the power of the\n\
castle.\n\
Do you want to Save?\n\
\n\
//You Bet//Not Now"))

//toad saved
DEFINE_DIALOG(DIALOG_015, 1, 4, 30, 200, _("\
Thanks for saving me\n\
again!\n\
\n\
\n\
You don't mind me\n\
living on your porch\n\
till I find a way off\n\
the island, right?...\n\
Hey, do you think there\n\
is a secret entrance\n\
to the inside of the\n\
island?"))

//egypt puzzle 1
DEFINE_DIALOG(DIALOG_016, 1, 2, 30, 200, _("\
Follow the 'shroom\n\
to find the next room."))

DEFINE_DIALOG(DIALOG_017, 1, 4, 30, 200, _("\
I'm the Big Bob-omb, lord\n\
of all blasting matter,\n\
king of ka-booms the\n\
world over!\n\
How dare you scale my\n\
mountain? By what right\n\
do you set foot on my\n\
imperial mountaintop?\n\
You may have eluded my\n\
guards, but you'll never\n\
escape my grasp...\n\
\n\
...and you'll never take\n\
away my Power Star. I\n\
hereby challenge you,\n\
Mario!\n\
If you want the Star I\n\
hold, you must prove\n\
yourself in battle.\n\
\n\
Can you pick me up from\n\
the back and hurl me to\n\
this royal turf? I think\n\
that you cannot!"))

//egypt puzzle 2
DEFINE_DIALOG(DIALOG_018, 1, 2, 30, 200, _("\
Think outside the box\n\
using your hops."))

//egypt puzzle 3
DEFINE_DIALOG(DIALOG_019, 1, 2, 30, 200, _("\
Start counting sheep\n\
and it's yours to keep."))

DEFINE_DIALOG(DIALOG_020, 1, 6, 95, 150, _("\
Dear Mario:\n\
Please come to the\n\
castle. I've baked\n\
a cake for you.\n\
Yours truly--\n\
Princess Toadstool"))

DEFINE_DIALOG(DIALOG_021, 1, 5, 95, 200, _("\
Welcome.\n\
No one's home!\n\
Now " SCRAM "\n\
and don't come back!\n\
Gwa ha ha!"))

DEFINE_DIALOG(DIALOG_022, 1, 2, 95, 200, _("\
You need a key to open\n\
this door."))

DEFINE_DIALOG(DIALOG_023, 1, 5, 95, 200, _("\
Thought you'd have an\n\
easy retirement on your\n\
private island?\n\
Tough luck!\n\
\n\
I sold the rights to\n\
all your adventures\n\
and now your mansion\n\
is locked!\n\
 -- Wahehehe\n\
(looks like you\n\
  may have to\n\
  go on some new\n\
  adventures...)"))

DEFINE_DIALOG(DIALOG_024, 1, 5, 95, 200, _("\
You need Star power to\n\
open this door. Recover a\n\
Power Star from an enemy\n\
inside one of the castle's\n\
paintings."))

DEFINE_DIALOG(DIALOG_025, 1, 4, 95, 200, _("\
It takes the power of\n\
3 Stars to open this\n\
door. You need [%] more\n\
Stars."))

DEFINE_DIALOG(DIALOG_026, 1, 4, 95, 200, _("\
It takes the power of\n\
8 Stars to open this\n\
door. You need [%] more\n\
Stars."))

DEFINE_DIALOG(DIALOG_027, 1, 4, 95, 200, _("\
It takes the power of\n\
30 Stars to open this\n\
door. You need [%] more\n\
Stars."))

DEFINE_DIALOG(DIALOG_028, 1, 4, 95, 200, _("\
It takes the power of\n\
50 Stars to open this\n\
door. You need [%] more\n\
Stars."))

DEFINE_DIALOG(DIALOG_029, 1, 5, 95, 200, _("\
To open the door that\n\
leads to the 『endless』\n\
stairs, you need 70\n\
Stars.\n\
Bwa ha ha!"))

//cleopatra act 1
DEFINE_DIALOG(DIALOG_030, 1, 4, 30, 200, _("\
Servant!\n\
Weird things are\n\
happening\n\
in my land!\n\
I want you to investigate.\n\
Go check and solve\n\
the mystery of the\n\
tomb to the east!"))

//cleopatra act 2
DEFINE_DIALOG(DIALOG_031, 1, 4, 30, 200, _("\
You solved the mystery\n\
of the tomb?\n\
Good job.\n\
But that didn't help.\n\
The water is still gone.\n\
Go check out the\n\
root of the Nile\n\
in the west.\n\
There may be a hint."))

//cleopatra act 3
DEFINE_DIALOG(DIALOG_032, 1, 4, 30, 200, _("\
Good job saving the Nile.\n\
My spys found there is\n\
a fake pharaoh in\n\
another pyramid.\n\
Do your empress a\n\
favor and dethrone\n\
him."))

//cleopatra act 4 5 6
DEFINE_DIALOG(DIALOG_033, 1, 3, 30, 200, _("\
The land is prospering\n\
again.\n\
Your work is appreciated.\n\
Go enjoy life and explore\n\
the country as you please."))

//toad1
DEFINE_DIALOG(DIALOG_034, 1, 2, 30, 200, _("\
This place is too\n\
hot for tuxedos..."))

//toad2
DEFINE_DIALOG(DIALOG_035, 1, 4, 30, 200, _("\
Queen! Queen!\n\
Anything and\n\
everything for\n\
Cleopatra!"))

//pharaoh
DEFINE_DIALOG(DIALOG_036, 1, 2, 30, 200, _("\
Did that she-devil\n\
send you?\n\
I do not tolerate\n\
intruders!\n\
Get lost!"))

DEFINE_DIALOG(DIALOG_037, 1, 2, 30, 200, _("\
I win! You lose!\n\
Ha ha ha ha!\n\
You're no slouch, but I'm\n\
a better sledder!\n\
Better luck next time!"))
//pirateguy
DEFINE_DIALOG(DIALOG_038, 1, 4, 95, 200, _("\
Cozy island!\n\
I've heard there's\n\
a treassure vault\n\
hidden in here.\n\
If only you had\n\
explosives!"))

//koopatown1 town entry
DEFINE_DIALOG(DIALOG_039, 1, 4, 30, 200, _("\
Welcome to our town!\n\
You can go surfing or\n\
admire the almighty\n\
ape here!"))

//koopatown2 gate
DEFINE_DIALOG(DIALOG_040, 1, 4, 30, 200, _("\
Noone can take\n\
my treasure!\n\
It is protected by\n\
this gate!\n\
And there is no switch\n\
to open it either!\n\
It's safe, haha!"))

DEFINE_DIALOG(DIALOG_041, 1, 3, 30, 200, _("\
I win! You lose!\n\
Ha ha ha!\n\
\n\
That's what you get for\n\
messin' with Koopa the\n\
Quick.\n\
Better luck next time!"))

//koopatown3z
DEFINE_DIALOG(DIALOG_042, 1, 4, 30, 200, _("\
That red coin?\n\
Yeah just take it,\n\
that currency is\n\
worthless here."))

//koopatown4
DEFINE_DIALOG(DIALOG_043, 1, 4, 30, 200, _("\
I live next to the\n\
great cannon we\n\
use to travel to the\n\
great ape!"))

//koopatown5
DEFINE_DIALOG(DIALOG_044, 1, 5, 95, 200, _("\
Secret underground\n\
Koopa society?\n\
No that wouldn't make\n\
sense, we Koopas\n\
love fresh air!"))

DEFINE_DIALOG(DIALOG_045, 1, 6, 95, 200, _("\
Whew! I'm just about\n\
flapped out. You should\n\
lay off the pasta, Mario!\n\
That's it for now. Press\n\
[A] to let go. Okay,\n\
bye byyyyyyeeee!"))

//koopatown6
DEFINE_DIALOG(DIALOG_046, 1, 5, 30, 200, _("\
This huge ladder is\n\
a symbol for the\n\
heroic deeds that\n\
the great ape has\n\
accomplished!"))

DEFINE_DIALOG(DIALOG_047, 1, 4, 95, 200, _("\
Hi! Sorry, I can't\n\
open cannons.\n\
Maybe that panther\n\
can help you out."))

//surfkoopa ask
DEFINE_DIALOG(DIALOG_048, 1, 4, 30, 200, _("\
Hey plumberboy!\n\
I'm Hunter the Koopa,\n\
the fastest surfer\n\
on this coast!\n\
Are you down for\n\
a race?\n\
\n\
//Yes/// No"))

//surfkoopa laugh cause declines
DEFINE_DIALOG(DIALOG_049, 1, 3, 30, 200, _("\
Haha, I suppose races\n\
are for rad people\n\
only."))

//surfkoopa explain rules
DEFINE_DIALOG(DIALOG_050, 1, 3, 30, 200, _("\
Alright here's the rules:\n\
First to finish the laps\n\
wins!\n\
Ready...set...go!"))

//surfkoopa taunt
DEFINE_DIALOG(DIALOG_051, 1, 2, 30, 200, _("\
Tough luck!\n\
\n\
I'm the raddest\n\
surfer around!"))

//surfkoopa surprised
DEFINE_DIALOG(DIALOG_052, 1, 2, 30, 200, _("\
That was rad!\n\
You totally beat me!\n\
Wow, take my star,\n\
you earned it!"))

//riddle 1
DEFINE_DIALOG(DIALOG_053, 1, 4, 30, 200, _("\
Welcome to the Pagoda\n\
of Riddles!\n\
\n\
\n\
To progress, you must\n\
answer my riddle correctly.\n\
The answer is 0, 1 or 2.\n\
Do you have the wisdom?\n\
Answer incorrectly and you\n\
shall be punished with\n\
a dangerous escape room.\n\
\n\
Imagine yourself in a race.\n\
You get ahead of the\n\
second placed person.\n\
Which spot are you in now?"))

//riddle 2
DEFINE_DIALOG(DIALOG_054, 1, 6, 30, 200, _("\
Exactly! To get ahead of\n\
the second place, you need\n\
to have been in third\n\
place before!\n\
The first place is still\n\
ahead of you.\n\
Now imagine 10 kids\n\
playing hide and seek.\n\
8 kids are already found.\n\
How many kids are\n\
still hiding?"))

DEFINE_DIALOG(DIALOG_055, 1, 4, 30, 200, _("\
Hey-ey, Mario, buddy,\n\
howzit goin'? Step right\n\
up. You look like a fast\n\
sleddin' kind of guy.\n\
I know speed when I see\n\
it, yes siree--I'm the\n\
world champion sledder,\n\
you know. Whaddya say?\n\
How about a race?\n\
Ready...\n\
\n\
//Go//// Don't Go"))

DEFINE_DIALOG(DIALOG_056, 1, 6, 30, 200, _("\
You brrrr-oke my record!\n\
Unbelievable! I knew\n\
that you were the coolest.\n\
Now you've proven\n\
that you're also the\n\
fastest!\n\
I can't award you a gold\n\
medal, but here, take this\n\
Star instead. You've\n\
earned it!"))

DEFINE_DIALOG(DIALOG_057, 1, 4, 30, 200, _("\
Egad! My baby!! Have you\n\
seen my baby??? She's\n\
the most precious baby in\n\
the whole wide world.\n\
(They say she has my\n\
beak...) I just can't\n\
remember where I left\n\
her.\n\
Let's see...I stopped\n\
for herring and ice cubes,\n\
then I...oohh! I just\n\
don't know!"))

DEFINE_DIALOG(DIALOG_058, 1, 4, 30, 200, _("\
You found my precious,\n\
precious baby! Where\n\
have you been? How can\n\
I ever thank you, Mario?\n\
Oh, I do have this...\n\
...Star. Here, take it\n\
with my eternal\n\
gratitude."))

DEFINE_DIALOG(DIALOG_059, 1, 4, 30, 200, _("\
That's not my baby! She\n\
looks nothing like me!\n\
Her parents must be\n\
worried sick!"))

//riddle 3
DEFINE_DIALOG(DIALOG_060, 1, 5, 30, 200, _("\
That's right!\n\
8 kids are found out,\n\
1 kid is seeking and\n\
only one is left hiding.\n\
Last one, listen up:\n\
3 Birds sit on a branch.\n\
You shoot one with a gun.\n\
How many birds are left\n\
on the branch?\n\
"))

//riddle 4
DEFINE_DIALOG(DIALOG_061, 1, 4, 30, 200, _("\
That was a trick one!\n\
The 2 other birds\n\
are going to fly away\n\
after a gunshot."))

//dragonriddle 1
DEFINE_DIALOG(DIALOG_062, 1, 3, 30, 200, _("\
We rank these\n\
5 different bells\n\
from biggest to smallest."))

//dragonriddle 2
DEFINE_DIALOG(DIALOG_063, 1, 3, 30, 200, _("\
The dragon sleeps...\n\
for now...\n\
until his song is played."))

//dragonriddle 3
DEFINE_DIALOG(DIALOG_064, 1, 2, 30, 200, _("\
The dragon's song goes:\n\
4, 1, 3, 2, 5."))

//tikiguy entry
DEFINE_DIALOG(DIALOG_065, 1, 2, 30, 200, _("\
Welcome to Shyvil!\n\
We are friendly fellas."))

//tikiguy smol
DEFINE_DIALOG(DIALOG_066, 1, 1, 30, 200, _("\
I love these flowers!"))

DEFINE_DIALOG(DIALOG_067, 1, 5, 30, 200, _("\
Tough luck, Mario!\n\
Princess Toadstool isn't\n\
here...Gwa ha ha!! Go\n\
ahead--just try to grab\n\
me by the tail!\n\
You'll never be able to\n\
swing ME around! A wimp\n\
like you won't throw me\n\
out of here! Never! Ha!"))
//tikiguy
DEFINE_DIALOG(DIALOG_068, 1, 4, 30, 200, _("\
Our elder is so wise!\n\
His battle techniques\n\
will win us the war\n\
against the Goombas.\n\
And then we take their\n\
treassure!"))

//tikiguy
DEFINE_DIALOG(DIALOG_069, 1, 4, 30, 200, _("\
This way leads out of\n\
our small village.\n\
Beware of the Goombas!\n\
They are very mean."))
//tiki elder
DEFINE_DIALOG(DIALOG_070, 1, 4, 30, 200, _("\
I'm the elder Guy!\n\
I protect this village.\n\
Recently we hear voices\n\
from this mountain.\n\
Something seems to be\n\
going on inside it..."))
//easterhead guy 0
DEFINE_DIALOG(DIALOG_071, 1, 4, 30, 200, _("\
Hello chum.\n\
I'm sticking way out.\n\
Please push my body\n\
back underground."))
//easterhead guy 1
DEFINE_DIALOG(DIALOG_072, 1, 3, 30, 200, _("\
Hey compadre.\n\
I can't see over here.\n\
Can you help me out?"))
//easterhead guy 2
DEFINE_DIALOG(DIALOG_073, 1, 3, 95, 200, _("\
Ahoy Amigo.\n\
My nose is itchy.\n\
Could you scratch it?"))
//easterhead guy 3
DEFINE_DIALOG(DIALOG_074, 1, 3, 30, 200, _("\
Greetings paisan.\n\
I'm getting bored\n\
looking in this direction.\n\
Cheer me up by running\n\
around me!"))
//easterhead guy 4
DEFINE_DIALOG(DIALOG_075, 1, 4, 30, 200, _("\
Evening, big man.\n\
This guy on my head is\n\
giving me a migraine.\n\
Please save me."))

DEFINE_DIALOG(DIALOG_076, 1, 6, 30, 200, _("\
Thanks to the power of\n\
the Stars, life is\n\
returning to the castle.\n\
Please, Mario, you have\n\
to give Bowser the boot!\n\
\n\
Here, let me tell you a\n\
little something about the\n\
castle. In the room with\n\
the mirrors, look carefully\n\
for anything that's not\n\
reflected in the mirror.\n\
And when you go to the\n\
water town, you can flood\n\
it with a high jump into\n\
the painting. Oh, by the\n\
way, look what I found!"))
//totemboss
DEFINE_DIALOG(DIALOG_077, 1, 1, 150, 200, _("\
Puny man.\n\
Can't climb pole.\n\
Will die by pole.\n\
For disturbing peace."))
//luigichariot talk
DEFINE_DIALOG(DIALOG_078, 1, 3, 30, 200, _("\
Hey, brother!\n\
I'm preparing my race\n\
Yoshi's for flight!\n\
Come back later and\n\
maybe I can show\n\
you their skill!"))

DEFINE_DIALOG(DIALOG_079, 1, 4, 30, 200, _("\
Owwwuu! Let me go!\n\
Uukee-kee! I was only\n\
teasing! Can't you take\n\
a joke?\n\
I'll tell you what, let's\n\
trade. If you let me go,\n\
I'll give you something\n\
really good.\n\
So, how about it?\n\
\n\
//Free him/ Hold on"))

DEFINE_DIALOG(DIALOG_080, 1, 1, 30, 200, _("\
Eeeh hee hee hee!"))

//luigichariot race proposal
DEFINE_DIALOG(DIALOG_081, 1, 4, 30, 200, _("\
Zeus took your\n\
signature hat?!\n\
Of course I will help\n\
you out, brother!\n\
But first, mind\n\
giving my Yoshis\n\
a test race?\n\
\n\
Let's race to my\n\
statue and then\n\
back to this cloud!\n\
//Yes/// No"))

//luigichariot talk after loss
DEFINE_DIALOG(DIALOG_082, 1, 4, 30, 200, _("\
Hehe, my Yoshis are\n\
ready to race!\n\
But you don't seem to,\n\
maybe lay off the pasta?\n\
You've gotta get in\n\
shape before fighting\n\
Zeus!"))

//raft toad
DEFINE_DIALOG(DIALOG_083, 1, 3, 30, 200, _("\
I paddled out to see to\n\
find treasure and now\n\
I'm stranded!\n\
Thank you for coming\n\
to my rescue!\n\
\n\
I don't want this stupid\n\
treasure any more!!"))

DEFINE_DIALOG(DIALOG_084, 1, 3, 30, 200, _("\
Yeeoww! Unhand me,\n\
brute! I'm late, so late,\n\
I must make haste!\n\
This shiny thing? Mine!\n\
It's mine. Finders,\n\
keepers, losers...\n\
Late, late, late...\n\
Ouch! Take it then! A\n\
gift from Bowser, it was.\n\
Now let me be! I have a\n\
date! I cannot be late\n\
for tea!"))

DEFINE_DIALOG(DIALOG_085, 1, 5, 30, 200, _("\
You don't stand a ghost\n\
of a chance in this house.\n\
If you walk out of here,\n\
you deserve...\n\
...a Ghoul Medal..."))

//luigichariot talk after win
DEFINE_DIALOG(DIALOG_086, 1, 4, 30, 200, _("\
Amazing brother!\n\
That Zeus guy won't\n\
stand a chance!\n\
\n\
An amazing runner\n\
like you needs\n\
amazing shoes!\n\
\n\
I have an idea,\n\
I'll give you these\n\
rainbow boots to walk\n\
on rainbows!"))

//zeus takes hat
DEFINE_DIALOG(DIALOG_087, 1, 3, 30, 200, _("\
A mortal came to visit\n\
the great Zeus?!\n\
\n\
That hat of yours\n\
looks like it would fit\n\
my head just right.\n\
I shall take it as\n\
an offering!"))
//zeus taunt after hat
DEFINE_DIALOG(DIALOG_088, 1, 4, 30, 200, _("\
Thanks for the gift!\n\
Hahaha!\n\
Huh, you don't look\n\
very happy...\n\
Fine, I'll let you\n\
have this blessing.\n\
Now scram!"))
//medusa threat
DEFINE_DIALOG(DIALOG_089, 1, 6, 95, 200, _("\
Who dares wander into\n\
Medusa's lair?!\n\
Did you come to steal\n\
back Wario's Wine?\n\
\n\
\n\
Pah, he should have\n\
invited me over!\n\
So what if you turn\n\
to stone when meeting\n\
my gaze?\n\
I'm great at parties!"))

DEFINE_DIALOG(DIALOG_090, 1, 6, 30, 200, _("\
Bwa ha ha ha!\n\
You've stepped right into\n\
my trap, just as I knew\n\
you would! I warn you,\n\
『Friend,』 watch your\n\
step!"))
//wario before medusa
DEFINE_DIALOG(DIALOG_091, 1, 3, 30, 200, _("\
That fiendish Medusa!\n\
She stole my wine!\n\
Now we can't have a party.\n\
If you slay that snake\n\
for me, you'll be invited!\n\
I'll do you any favor!\n\
Her cave's at the back\n\
of the Olymp."))

DEFINE_DIALOG(DIALOG_092, 1, 5, 30, 200, _("\
Pestering me again, are\n\
you, Mario? Can't you see\n\
that I'm having a merry\n\
little time, making\n\
mischief with my minions?\n\
Now, return those Stars!\n\
My troops in the walls\n\
need them! Bwa ha ha!"))

DEFINE_DIALOG(DIALOG_093, 1, 5, 30, 200, _("\
Mario! You again! Well\n\
that's just fine--I've\n\
been looking for something\n\
to fry with my fire\n\
breath!\n\
Your Star Power is\n\
useless against me!\n\
Your friends are all\n\
trapped within the\n\
walls...\n\
And you'll never see the\n\
Princess again!\n\
Bwa ha ha ha!"))
//wario after medusa
DEFINE_DIALOG(DIALOG_094, 1, 3, 30, 200, _("\
BWAHAHA you showed that\n\
witch!\n\
\n\
If you want to go up\n\
against Zeus, you can\n\
use my ship.\n\
I'm tired of\n\
seeing his stupid\n\
face on this mountain."))
//wario during zeus
DEFINE_DIALOG(DIALOG_095, 1, 3, 30, 200, _("\
My ship is waiting\n\
for you at the peak!\n\
Hop on and beat Zeus!"))
//wario after zeus
DEFINE_DIALOG(DIALOG_096, 1, 3, 30, 200, _("\
HAHAHA he deserved\n\
that whooping!\n\
Good job, brother.\n\
That's what he gets\n\
for ruining my view\n\
with his nasty face!"))
//zeus bossfight start
DEFINE_DIALOG(DIALOG_097, 1, 4, 30, 200, _("\
You dare oppose the\n\
great Zeus?!\n\
You risk your life for\n\
what, your hat?\n\
I will crush this\n\
feeble attempt at\n\
conspiracy!"))

DEFINE_DIALOG(DIALOG_098, 1, 2, 95, 200, _("\
Come on in here...\n\
...heh, heh, heh..."))

// unused
DEFINE_DIALOG(DIALOG_099, 1, 5, 95, 200, _("\
Eh he he...\n\
You're mine, now, hee hee!\n\
I'll pass right through\n\
this wall. Can you do\n\
that? Heh, heh, heh!"))

DEFINE_DIALOG(DIALOG_100, 1, 3, 95, 200, _("\
Ukkiki...Wakkiki...kee kee!\n\
Ha! I snagged it!\n\
It's mine! Heeheeheeee!"))

DEFINE_DIALOG(DIALOG_101, 1, 3, 95, 200, _("\
Ackk! Let...go...\n\
You're...choking...me...\n\
Cough...I've been framed!\n\
This Cap? Oh, all right,\n\
take it. It's a cool Cap,\n\
but I'll give it back.\n\
I think it looks better on\n\
me than it does on you,\n\
though! Eeeee! Kee keee!"))

DEFINE_DIALOG(DIALOG_102, 1, 5, 30, 200, _("\
Pssst! The Boos are super\n\
shy. If you look them\n\
in the eyes, they fade\n\
away, but if you turn\n\
your back, they reappear.\n\
It's no use trying to hit\n\
them when they're fading\n\
away. Instead, sneak up\n\
behind them and punch."))
//zeus after fight
DEFINE_DIALOG(DIALOG_103, 1, 4, 95, 200, _("\
A mortal...\n\
but how?!\n\
I'm a god!\n\
This is frivolous!"))
//lkuigi zeus fight
DEFINE_DIALOG(DIALOG_104, 1, 4, 30, 200, _("\
Hey bro!\n\
I'm here to help out.\n\
I brought you a\n\
Pegasus Yoshi!\n\
Hop on it and fly it\n\
into Zeus!\n\
That's gonna hurt."))

DEFINE_DIALOG(DIALOG_105, 1, 3, 95, 200, _("\
Ready for blastoff! Come\n\
on, hop into the cannon!\n\
\n\
You can reach the Star on\n\
the floating island by\n\
using the four cannons.\n\
Use the Control Stick to\n\
aim, then press [A] to fire.\n\
\n\
If you're handy, you can\n\
grab on to trees or poles\n\
to land."))

DEFINE_DIALOG(DIALOG_106, 1, 2, 95, 200, _("\
Ready for blastoff! Come\n\
on, hop into the cannon!"))

DEFINE_DIALOG(DIALOG_107, 1, 3, 95, 200, _("\
Ghosts...\n\
...don't...\n\
...DIE!\n\
Heh, heh, heh!\n\
Can you get out of here...\n\
...alive?"))

DEFINE_DIALOG(DIALOG_108, 1, 2, 95, 200, _("\
Boooooo-m! Here comes\n\
the master of mischief,\n\
the tower of terror,\n\
the Big Boo!\n\
Ka ha ha ha..."))
//namek elder intro
DEFINE_DIALOG(DIALOG_109, 1, 6, 95, 200, _("\
You are a good guy,\n\
I can feel it in your\n\
energy profile.\n\
Our planet is under attack!\n\
I sense your latent\n\
strength.\n\
I'll awaken it for you\n\
Please help us!\n\
\n\
\n\
\n\
\n\
With your potential\n\
unlocked,\n\
you can press A\n\
during a jump to fly\n\
until your KI\n\
is used up."))
//namek elder elsewise
DEFINE_DIALOG(DIALOG_110, 1, 4, 95, 200, _("\
Our savior!\n\
Your name will be\n\
written into\n\
namekian history!"))
//namek welcome text
DEFINE_DIALOG(DIALOG_111, 1, 4, 95, 200, _("\
Now that you've\n\
reached Namek and\n\
had your potential\n\
unlocked,\n\
you can press A\n\
during a jump to fly\n\
until your KI\n\
is used up.\n\
Refill your KI on the\n\
floor."))
//namekian 1
DEFINE_DIALOG(DIALOG_112, 1, 4, 30, 200, _("\
Our neighbouring village\n\
got destroyed!\n\
\n\
\n\
I wonder if the\n\
perpetrators were\n\
after our\n\
dragon balls?"))
//namekian 2
DEFINE_DIALOG(DIALOG_113, 1, 3, 30, 200, _("\
The elder created\n\
magic dragon balls!\n\
\n\
Collecting all seven\n\
of them makes your\n\
wish come true!"))

DEFINE_DIALOG(DIALOG_114, 1, 5, 95, 200, _("\
It makes me so mad! We\n\
build your houses, your\n\
castles. We pave your\n\
roads, and still you\n\
walk all over us.\n\
Do you ever say thank\n\
you? No! Well, you're not\n\
going to wipe your feet\n\
on me! I think I'll crush\n\
you just for fun!\n\
Do you have a problem\n\
with that? Just try to\n\
pound me, wimp! Ha!"))
//king bob omb pirate
DEFINE_DIALOG(DIALOG_115, 1, 4, 95, 200, _("\
Enemy ship spotted!\n\
Shoot the cannons!\n\
Your loot shall be\n\
mine!\n\
Bet he won't be\n\
able to kick those\n\
back at us,\n\
harr harr!"))

//king bob omb pirate
DEFINE_DIALOG(DIALOG_116, 1, 3, 95, 200, _("\
Stop the war!\n\
My beloved ship can't\n\
take this abuse!\n\
You win!\n\
Take this booty and\n\
leave!"))

DEFINE_DIALOG(DIALOG_117, 1, 1, 95, 200, _("\
Who...walk...here?\n\
Who...break...seal?\n\
Wake..ancient..ones?\n\
We no like light...\n\
Rrrrummbbble...\n\
We no like...intruders!\n\
Now battle...\n\
...hand...\n\
...to...\n\
...hand!"))

DEFINE_DIALOG(DIALOG_118, 1, 6, 95, 200, _("\
Grrrrumbbble!\n\
What...happen?\n\
We...crushed like pebble.\n\
You so strong!\n\
You rule ancient pyramid!\n\
For today...\n\
Now, take Star of Power.\n\
We...sleep...darkness."))

DEFINE_DIALOG(DIALOG_119, 1, 6, 30, 200, _("\
Grrr! I was a bit\n\
careless. This is not as I\n\
had planned...but I still\n\
hold the power of the\n\
Stars, and I still have\n\
Peach.\n\
Bwa ha ha! You'll get no\n\
more Stars from me! I'm\n\
not finished with you yet,\n\
but I'll let you go for\n\
now. You'll pay for this...\n\
later!"))

DEFINE_DIALOG(DIALOG_120, 1, 4, 30, 200, _("\
Ooowaah! Can it be that\n\
I've lost??? The power of\n\
the Stars has failed me...\n\
this time.\n\
Consider this a draw.\n\
Next time, I'll be in\n\
perfect condition.\n\
\n\
Now, if you want to see\n\
your precious Princess,\n\
come to the top of the\n\
tower.\n\
I'll be waiting!\n\
Gwa ha ha ha!"))

DEFINE_DIALOG(DIALOG_121, 1, 5, 30, 200, _("\
Nooo! It can't be!\n\
You've really beaten me,\n\
Mario?!! I gave those\n\
troops power, but now\n\
it's fading away!\n\
Arrgghh! I can see peace\n\
returning to the world! I\n\
can't stand it! Hmmm...\n\
It's not over yet...\n\
\n\
C'mon troops! Let's watch\n\
the ending together!\n\
Bwa ha ha!"))

//namekian 3
DEFINE_DIALOG(DIALOG_122, 1, 4, 30, 200, _("\
Our elder is amazing!\n\
Every village protects\n\
one of the dragon balls\n\
He's created."))

//namekian 4
DEFINE_DIALOG(DIALOG_123, 1, 4, 30, 200, _("\
The dragon balls are\n\
hidden all over namek!\n\
\n\
\n\
One scientist actually\n\
build a radar to find\n\
them too.\n\
Too bad she went missing."))

//namekian 5
DEFINE_DIALOG(DIALOG_124, 1, 3, 30, 200, _("\
The villains that landed\n\
on our planet can't find\n\
the dragon balls!\n\
If they do, who knows\n\
what they'll wish\n\
for..."))
//bulma text
DEFINE_DIALOG(DIALOG_125, 1, 4, 30, 200, _("\
Oh hey there little\n\
man!\n\
You are a friend of\n\
the namekians?\n\
That's great!\n\
I've been trying to\n\
find the dragon balls\n\
with my radar.\n\
I'll lend you my radar\n\
if you promise not to\n\
use that wish on\n\
yourself!\n\
Here you go!"))
//namek elder act 2
DEFINE_DIALOG(DIALOG_126, 2, 4, 30, 200, _("\
Did you come to our\n\
planet to find the\n\
dragon balls?\n\
\n\
There was a scientist\n\
with the same goal.\n\
She's stuck in the\n\
outer ring of mountains."))

//bulma other acts
DEFINE_DIALOG(DIALOG_127, 3, 4, 30, 200, _("\
How's it going?\n\
Already found the\n\
dragon balls?\n\
Hurry up!\n\
I need my wish for\n\
a charming, handsome\n\
boyfriend to come true\n\
before I get old!"))

DEFINE_DIALOG(DIALOG_128, 1, 4, 95, 200, _("\
You must fight with\n\
honor! It is against the\n\
royal rules to throw the\n\
king out of the ring!"))
//namek elder act 4
DEFINE_DIALOG(DIALOG_129, 1, 3, 30, 200, _("\
You almost have all the\n\
dragon balls in our\n\
village now!\n\
The last one should be\n\
in our enemies'\n\
spaceship.\n\
Once you have the last\n\
one, you can make a\n\
wish and save us all!"))
//dragonball steal
DEFINE_DIALOG(DIALOG_130, 1, 4, 30, 200, _("\
You found the\n\
Dragon Ball!\n\
\n\
\n\
Now you just need\n\
to carry it back\n\
out of this ship\n\
alive!"))

//walufreeza kills mario
DEFINE_DIALOG(DIALOG_131, 1, 5, 30, 200, _("\
You little Goomba!\n\
You stole my Dragon\n\
Ball?!\n\
\n\
\n\
I am Walufreeza, the\n\
emperor of the universes\n\
and I will be the one to\n\
have my wish granted!\n\
Die you fool!"))

DEFINE_DIALOG(DIALOG_132, 1, 4, 30, 200, _("\
Whoa, Mario, pal, you\n\
aren't trying to cheat,\n\
are you? Shortcuts aren't\n\
allowed.\n\
Now, I know that you\n\
know better. You're\n\
disqualified! Next time,\n\
play fair!"))
//namekian revived
DEFINE_DIALOG(DIALOG_133, 1, 4, 30, 200, _("\
It worked!!\n\
We used the Dragon Balls\n\
to bring you back from\n\
the dead!\n\
Walufreeza slaughtered\n\
the whole village\n\
while you were gone!\n\
\n\
Please, accept all\n\
my energy and save our\n\
planet!\n\
I believe in you."))

//walufreeza revived
DEFINE_DIALOG(DIALOG_134, 1, 5, 30, 200, _("\
What?!\n\
Did I not just kill you?\n\
They used the Dragon\n\
Balls to bring you\n\
back?!\n\
Now my wish won't\n\
be granted!!\n\
I hate you!"))

//walufreeza pissed off
DEFINE_DIALOG(DIALOG_135, 1, 2, 30, 200, _("\
Now you've done it!\n\
I'm really mad!\n\
No more holding back,\n\
this is my real form!"))

//walufreeza after transform
DEFINE_DIALOG(DIALOG_136, 1, 3, 30, 200, _("\
Wahehehe!\n\
This form makes me\n\
twice as strong!\n\
Now die!"))
//walufreeza post fight
DEFINE_DIALOG(DIALOG_137, 1, 2, 30, 200, _("\
Grrr...\n\
What are you?\n\
I can't...\n\
believe this..."))

//pirate sign
DEFINE_DIALOG(DIALOG_138, 1, 5, 30, 200, _("\
You want my treasure?\n\
Good luck, my sea\n\
monster is guarding it!\n\
He'll eat you in one bite.\n\
-- The Captain"))
//latebunny1
DEFINE_DIALOG(DIALOG_139, 1, 2, 30, 200, _("\
Can't talk,\n\
I'm already late!"))
//latebunny2
DEFINE_DIALOG(DIALOG_140, 1, 3, 30, 200, _("\
I'm sorry I really\n\
can't talk!\n\
I'm late!"))
//latebunny3
DEFINE_DIALOG(DIALOG_141, 1, 2, 150, 200, _("\
Gotta go!\n\
I'm already late!"))
//thwomp
DEFINE_DIALOG(DIALOG_142, 1, 5, 150, 200, _("\
Hehe I'm blocking you\n\
off, softie!\n\
Do you have an explosive\n\
partner?\n\
If not, tough luck, softie!"))

DEFINE_DIALOG(DIALOG_143, 1, 6, 150, 200, _("\
You've recovered eight of\n\
the Power Stars! Now you\n\
can open the door with\n\
the big Star! But Bowser\n\
is just ahead...can you\n\
hear the Princess calling?"))

DEFINE_DIALOG(DIALOG_144, 1, 6, 150, 200, _("\
You've recovered 30\n\
Power Stars! Now you can\n\
open the door with the\n\
big Star! But before you\n\
move on, how's it going\n\
otherwise?\n\
Did you pound the two\n\
columns down? You didn't\n\
lose your hat, did you?\n\
If you did, you'll have to\n\
stomp on the condor to\n\
get it back!\n\
They say that Bowser has\n\
sneaked out of the sea\n\
and into the underground.\n\
Have you finally\n\
cornered him?"))

DEFINE_DIALOG(DIALOG_145, 1, 6, 150, 200, _("\
You've recovered 50\n\
Power Stars! Now you can\n\
open the Star Door on the\n\
third floor. Bowser's\n\
there, you know.\n\
\n\
Oh! You've found all of\n\
the Cap Switches, haven't\n\
you? Red, green and blue?\n\
The Caps you get from the\n\
colored blocks are really\n\
helpful.\n\
Hurry along, now. The\n\
third floor is just ahead."))
//toad lawyer
DEFINE_DIALOG(DIALOG_146, 1, 5, 150, 200, _("\
It's really you, Mario!\n\
I have great news!\n\
\n\
\n\
\n\
Your recent adventures\n\
helped me put together a\n\
great case and we might\n\
get your copyrights and\n\
your mansion back!\n\
Are you ready to\n\
go to trial?\n\
\n\
\n\
//Yes////No"))
//dinnerbunny act1
DEFINE_DIALOG(DIALOG_147, 1, 3, 30, 200, _("\
Finally tea time!\n\
Almost missed my own\n\
unbirthday!"))

//madhatter act1
DEFINE_DIALOG(DIALOG_148, 1, 5, 30, 200, _("\
Oh hey, Mario!\n\
It is your own\n\
unbirthday too today,\n\
isn't it?\n\
Join us for tea!"))

//chinaboss
DEFINE_DIALOG(DIALOG_149, 1, 2, 30, 200, _("\
I guard this tower!\n\
Begone intruder!"))
//wingo1
DEFINE_DIALOG(DIALOG_150, 1, 3, 30, 200, _("\
Heh, they have some nice\n\
silverware there...\n\
So shiny..."))
//wingo1
DEFINE_DIALOG(DIALOG_151, 1, 2, 30, 200, _("\
Are you after this cool\n\
shiny I found?\n\
Bah! Go away!\n\
It's mine!"))
//wingo1
DEFINE_DIALOG(DIALOG_152, 1, 5, 30, 200, _("\
Alright stop!\n\
I'm flapped out!\n\
\n\
\n\
\n\
I'll give you this\n\
other shiny if you\n\
promise not to\n\
tell anyone where\n\
my nest is!"))

//wingo1
DEFINE_DIALOG(DIALOG_153, 1, 4, 30, 200, _("\
Hey! Who's there?\n\
What's climbing on me?\n\
Is it an ice ant?\n\
A snow flea?\n\
Whatever it is, it's\n\
bugging me! I think I'll\n\
blow it away!"))
//luigi hatter stolen silverware
DEFINE_DIALOG(DIALOG_154, 1, 3, 30, 200, _("\
The bird swooped\n\
in and stole our\n\
silverware!\n\
Do you think I could\n\
pour the tea in my\n\
hat and drink from it?"))
//thwomptoad
DEFINE_DIALOG(DIALOG_155, 1, 3, 30, 200, _("\
GIVE ME FOUR OF\n\
A KIND TO AWAKEN\n\
THE BUP"))

//raft toad
DEFINE_DIALOG(DIALOG_156, 1, 3, 30, 200, _("\
I'll swim to your\n\
island!\n\
Thanks for letting me stay."))

//huffnpuff post fight
DEFINE_DIALOG(DIALOG_157, 1, 4, 30, 200, _("\
You meanie!\n\
Fine, I'll give you this!\n\
Just stop beating my face\n\
already!"))

//huffnpuff before fight
DEFINE_DIALOG(DIALOG_158, 1, 2, 30, 200, _("\
Hey! What are you\n\
doing on my palace!\n\
I'll zap the\n\
jumpy out of you!"))

//pokemontexts
DEFINE_DIALOG(DIALOG_159, 1, 3, 30, 200, _("\
You've unlocked Staryu!\n\
Press the L button to\n\
make it come out.\n\
It'll use Aquagun to\n\
give you a height boost."))

//pokemontexts
DEFINE_DIALOG(DIALOG_160, 1, 4, 30, 200, _("\
You've captured Weezing!\n\
Press the L button to\n\
make him come out!\n\
\n\
You can jump on him\n\
to float through\n\
the air for a\n\
shot period."))


//pokemontexts
DEFINE_DIALOG(DIALOG_161, 1, 4, 30, 200, _("\
You've captured Tangela!\n\
Press the L button to\n\
make her come out!\n\
\n\
She will shoot out\n\
a vine whip and\n\
carry you to a nearby\n\
wall!"))

//pokemontexts
DEFINE_DIALOG(DIALOG_162, 1, 3, 30, 200, _("\
You've got a Haunter!\n\
Press L to have him\n\
turn you invisible."))

//pokemontexts
DEFINE_DIALOG(DIALOG_163, 1, 3, 30, 200, _("\
You've captured Onix!\n\
Press the L button to\n\
make it come out!\n\
It will build a\n\
bridge and let you\n\
walk on it!"))

//pokemontexts
DEFINE_DIALOG(DIALOG_164, 1, 3, 30, 200, _("\
You got Primeape!\n\
Make him come out with\n\
the L button.\n\
He will use Seismic Toss\n\
and throw you far up!"))

//pokemontexts
DEFINE_DIALOG(DIALOG_165, 1, 3, 30, 200, _("\
You've unlocked Golem.\n\
Press L to spawn the\n\
explosive Pokemon!"))
//pirate
DEFINE_DIALOG(DIALOG_166, 1, 3, 30, 200, _("\
Ahoy Matey!\n\
I'm looking for\n\
treassure!\n\
It's marked on\n\
my map with an X.\n\
\n\
I'll mark the island\n\
for you! Maybe you have\n\
better luck."))
//panther post shop
DEFINE_DIALOG(DIALOG_167, 1, 2, 30, 200, _("\
Come back any time\n\
you need my services!"))

DEFINE_DIALOG(DIALOG_168, 1, 3, 30, 200, _("\
You've unlocked Gyarados!\n\
Press L to spawn it.\n\
\n\
It'll let you surf on it...\n\
but please don't spawn\n\
this guy on land."))
//panther pre shop
DEFINE_DIALOG(DIALOG_169, 1, 4, 30, 200, _("\
What's up buddy?\n\
Can I hook you up\n\
with anything specific\n\
today?\n\
Check out my inventory\n\
and tell me what you'll\n\
need!"))
//articuno
DEFINE_DIALOG(DIALOG_170, 1, 3, 30, 200, _("\
You've unlocked Articuno!\n\
Press the L button to\n\
spawn it!\n\
It'll use Icebeam and\n\
make a pole for you!"))
//magnemite
DEFINE_DIALOG(DIALOG_171, 1, 4, 30, 200, _("\
You've unlocked Magnemite!\n\
Press the L button to\n\
call your buddy to\n\
help you collect coins!"))
//hypno
DEFINE_DIALOG(DIALOG_172, 1, 4, 30, 200, _("\
Need to take a nap and\n\
recover?\n\
\n\
\n\
Press the L button to\n\
spawn Hypno to help\n\
you fall asleep\n\
and regenerate health."))
//dkcourt
DEFINE_DIALOG(DIALOG_173, 1, 4, 30, 200, _("\
I am the Judge Kong\n\
presiding the case of\n\
Mario vs Waluigi.\n\
\n\
Waluigi is being\n\
accused of having\n\
stolen the copyrights\n\
for Mario's adventures.\n\
May justice prevail!"))


DEFINE_DIALOG(DIALOG_174, 1, 4, 30, 200, _("\
I am Attorney Wario and\n\
will prove beyond any\n\
doubt the innocence of\n\
my client.\n\
Wahahaha!"))


DEFINE_DIALOG(DIALOG_175, 1, 2, 30, 200, _("\
Yes innocent!\n\
Wahehehe!"))


DEFINE_DIALOG(DIALOG_176, 1, 4, 30, 200, _("\
Yeeeoww!\n\
I'm attorney Toad.\n\
I believe I have built\n\
a convincing case.\n\
We will get Mario's\n\
copyrights back today!"))


DEFINE_DIALOG(DIALOG_177, 1, 1, 30, 200, _("\
Mama mia!"))

DEFINE_DIALOG(DIALOG_178, 1, 7, 30, 200, _("\
Well then, introductions\n\
out of the way, how do\n\
you intend to prove\n\
that Waluigi's famous\n\
adventures were indeed\n\
stories of Mario's\n\
adventures?"))
DEFINE_DIALOG(DIALOG_179, 1, 6, 30, 200, _("\
Your honor, to prove\n\
that Mario is the one\n\
doing the adventuring,\n\
this man has been\n\
visiting places all\n\
over the world.\n\
He's met countless\n\
people and their\n\
stories show that he\n\
is indeed a hero!"))
DEFINE_DIALOG(DIALOG_180, 1, 1, 30, 200, _("\
Yahoo!"))
DEFINE_DIALOG(DIALOG_181, 1, 4, 30, 200, _("\
I have read that in\n\
the news!\n\
Lots of people love\n\
this Mario guy!"))
DEFINE_DIALOG(DIALOG_182, 1, 4, 30, 200, _("\
Oh no!\n\
But your honor, even if\n\
there are reports of\n\
Mario being a hero,\n\
we have witnesses\n\
proving that Waluigi\n\
beat all those baddies!"))
DEFINE_DIALOG(DIALOG_183, 1, 1, 30, 200, _("\
Loser!"))
DEFINE_DIALOG(DIALOG_184, 1, 1, 30, 200, _("\
Oof!"))
DEFINE_DIALOG(DIALOG_185, 1, 4, 30, 200, _("\
Hehe stinky!\n\
Your honor, may I\n\
call my first\n\
witness?"))
DEFINE_DIALOG(DIALOG_186, 1, 1, 30, 200, _("\
Okay!"))
DEFINE_DIALOG(DIALOG_187, 1, 3, 30, 200, _("\
Witness number one,\n\
please introduce\n\
yourself."))
DEFINE_DIALOG(DIALOG_188, 1, 3, 30, 200, _("\
IM CHOMP!\n\
I LIKE FOOD!\n\
I EAT THE PLUMBER."))
DEFINE_DIALOG(DIALOG_189, 1, 3, 30, 200, _("\
The plumber?\n\
I think you meant\n\
to say the lanky man!\n\
Remember what we\n\
talked about."))
DEFINE_DIALOG(DIALOG_190, 1, 3, 30, 200, _("\
ERR, YES.\n\
I EAT THE\n\
LANKY MAN."))
DEFINE_DIALOG(DIALOG_191, 1, 2, 30, 200, _("\
That's a me!\n\
Wahehehe!"))
DEFINE_DIALOG(DIALOG_192, 1, 3, 30, 200, _("\
Thank your for being\n\
honest, Mister Chomp.\n\
\n\
Would you mind detailing\n\
how your encounter with\n\
the lanky man went?"))
DEFINE_DIALOG(DIALOG_193, 1, 1, 30, 200, _("\
I GUARD THE GATE.\n\
THE LANKY MAN COMES.\n\
HE STOMPS MY POLE.\n\
I AM NOW FREE.\n\
FAT MAN OFFERS MEAT.\n\
I COME HERE."))
DEFINE_DIALOG(DIALOG_194, 1, 2, 30, 200, _("\
Oh no!\n\
\n\
There was no meat\n\
involved your honor!"))
DEFINE_DIALOG(DIALOG_195, 1, 2, 30, 200, _("\
Someone offered you\n\
meat to come here?"))
DEFINE_DIALOG(DIALOG_196, 1, 2, 30, 200, _("\
BUT FAT MAN SAID\n\
THERE WOULD BE MEAT."))
DEFINE_DIALOG(DIALOG_197, 1, 4, 30, 200, _("\
Well, regardless of\n\
who this 'FAT MAN' is,\n\
Chomp's story seems to\n\
support the defense.\n\
Mr Toad, would you like\n\
to cross examine the\n\
witness?"))
DEFINE_DIALOG(DIALOG_198, 1, 5, 30, 200, _("\
His story checks out...\n\
Mario, are you sure it's\n\
you that freed the\n\
Chain Chomp?...\n\
\n\
I can't find a flaw.\n\
What do you want to\n\
ask Mr Chomp?\n\
\n\
\n\
1) Isn't Waluigi too\n\
   cowardly to free you?\n\
2) Did the defense\n\
   attorney offer meat?\n\
//1)////2)"))
DEFINE_DIALOG(DIALOG_199, 1, 3, 30, 200, _("\
Isn't Waluigi too\n\
cowardly to sneak\n\
past a monster like that?"))
DEFINE_DIALOG(DIALOG_200, 1, 1, 30, 200, _("\
Haha!"))
DEFINE_DIALOG(DIALOG_201, 1, 3, 30, 200, _("\
I can't believe you\n\
would be so rude!\n\
\n\
Judge Kong,\n\
this man is\n\
unprofessional!"))
DEFINE_DIALOG(DIALOG_202, 1, 3, 30, 200, _("\
Mr Toad!!\n\
This is unbelieveable.\n\
This is not"))
DEFINE_DIALOG(DIALOG_203, 1, 1, 30, 200, _("\
Okay!"))
DEFINE_DIALOG(DIALOG_204, 1, 4, 30, 200, _("\
Im so sorry!\n\
Looks like we really\n\
messed this one up,\n\
Mario."))
DEFINE_DIALOG(DIALOG_205, 1, 4, 30, 200, _("\
Your honor,\n\
Mr Chomp has clearly\n\
been bribed with meat\n\
by the defense attorney!\n\
When Mr Chomp mentions\n\
'FAT MAN', he is talking\n\
about Wario!"))
DEFINE_DIALOG(DIALOG_206, 1, 1, 30, 200, _("\
Here we go!"))
DEFINE_DIALOG(DIALOG_207, 1, 3, 30, 200, _("\
Objection!\n\
That is pure\n\
speculation!"))
DEFINE_DIALOG(DIALOG_208, 1, 2, 30, 200, _("\
Yes stipulation!\n\
Wahehehe!"))
DEFINE_DIALOG(DIALOG_209, 1, 3, 30, 200, _("\
Quiet!\n\
Unfortunately I have to\n\
disqualify this witness.\n\
It is evident he's been\n\
set up."))
DEFINE_DIALOG(DIALOG_210, 1, 1, 30, 200, _("\
This is rotten!"))
DEFINE_DIALOG(DIALOG_211, 1, 1, 30, 200, _("\
Cheaters!"))
DEFINE_DIALOG(DIALOG_212, 1, 1, 30, 200, _("\
Haha Hahaha HAAAAA!"))
DEFINE_DIALOG(DIALOG_213, 1, 2, 30, 200, _("\
Well this is not\n\
nearly it!\n\
We have two more\n\
witnesses!"))
DEFINE_DIALOG(DIALOG_214, 1, 1, 30, 200, _("\
WOOOAAAOOOOWWWW!"))
DEFINE_DIALOG(DIALOG_215, 1, 3, 30, 200, _("\
Don't dispair, Mario!\n\
We've got a solid\n\
case!"))
DEFINE_DIALOG(DIALOG_216, 1, 2, 30, 200, _("\
Another witness?\n\
Well, let's hear them."))
DEFINE_DIALOG(DIALOG_217, 1, 1, 30, 200, _("\
You are doomed, Mario!"))
DEFINE_DIALOG(DIALOG_218, 1, 2, 30, 200, _("\
Enough!\n\
Bring the witness in."))
DEFINE_DIALOG(DIALOG_219, 1, 2, 30, 200, _("\
Hi!\n\
I'm Snappy the plant."))
DEFINE_DIALOG(DIALOG_220, 1, 3, 30, 200, _("\
Well then Snappy,\n\
let's start the\n\
cross examination!\n\
The defense may ask\n\
questions first."))

DEFINE_DIALOG(DIALOG_221, 1, 3, 30, 200, _("\
Witness number two,\n\
please introduce\n\
yourself."))
DEFINE_DIALOG(DIALOG_222, 1, 3, 30, 200, _("\
Miss Snappy, could you\n\
elaborate on what you\n\
do for a living?"))

DEFINE_DIALOG(DIALOG_223, 1, 4, 30, 200, _("\
I sleep at the foot\n\
of Whomp's Fortress.\n\
My job is to bite any\n\
intruders."))

DEFINE_DIALOG(DIALOG_224, 1, 3, 30, 200, _("\
So have you ever\n\
seen Waluigi enter\n\
the fortress?"))

DEFINE_DIALOG(DIALOG_225, 1, 2, 30, 200, _("\
Yes, I saw him with\n\
my own two eyes!\n\
I tried to bite him,\n\
but he didn't come close."))

DEFINE_DIALOG(DIALOG_226, 1, 1, 30, 200, _("\
You heard her!\n\
Loser!\n\
Wahehehe!"))

DEFINE_DIALOG(DIALOG_227, 1, 4, 30, 200, _("\
Calm it!\n\
Mr Toad,\n\
do you have any\n\
questions?"))

DEFINE_DIALOG(DIALOG_228, 1, 5, 30, 200, _("\
Yes your honor!\n\
Miss Snappy, have\n\
you actually seen\n\
Waluigi do anything\n\
in Whomp's Fortress?"))

DEFINE_DIALOG(DIALOG_229, 1, 4, 30, 200, _("\
Yes!\n\
He ground pounded\n\
the Whomp King and\n\
freed the fortress!\n\
I saw it with my\n\
own two eyes!"))
DEFINE_DIALOG(DIALOG_230, 1, 5, 30, 200, _("\
Oh no!\n\
That makes perfect\n\
sense!\n\
Mario, do you have any\n\
ideas?\n\
1) You don't even have\n\
   eyes!\n\
2) Waluigi smells too\n\
   much to sneak in!\n\
//1)////2"))
DEFINE_DIALOG(DIALOG_231, 1, 3, 30, 200, _("\
This witness claims\n\
to be an eyewitness\n\
despite not having eyes!\n\
This is highly suspicious!"))
DEFINE_DIALOG(DIALOG_232, 1, 3, 30, 200, _("\
This doesn't check out!\n\
Waluigi's smell would\n\
have alerted everyone!\n\
There is no way\n\
he managed to sneak in!"))
DEFINE_DIALOG(DIALOG_233, 1, 3, 30, 200, _("\
Wow you are right!\n\
This witness is clearly\n\
unreliable!\n\
I am sorry, but I\n\
will have to disqualify\n\
this witness as well."))
DEFINE_DIALOG(DIALOG_234, 1, 2, 30, 200, _("\
How rude!\n\
My hubris hurts!"))
DEFINE_DIALOG(DIALOG_235, 1, 3, 30, 200, _("\
Mr Toad!\n\
Please stay on topic.\n\
Insults won't help."))
DEFINE_DIALOG(DIALOG_236, 1, 2, 30, 200, _("\
I really fricked this\n\
on up, Mario!\n\
So sorry!"))
DEFINE_DIALOG(DIALOG_237, 1, 3, 30, 200, _("\
Great job, Mario!\n\
Their defense is\n\
crumbling!"))
DEFINE_DIALOG(DIALOG_238, 1, 3, 30, 200, _("\
Now then, defense,\n\
do you have a witness\n\
that actually has eyes?"))
DEFINE_DIALOG(DIALOG_239, 1, 3, 30, 200, _("\
Of course,\n\
your honor!\n\
\n\
And I guarantee it's\n\
a good one!\n\
Wahahaha"))
DEFINE_DIALOG(DIALOG_240, 1, 2, 30, 200, _("\
It's a good one!\n\
Wahehehe!"))
DEFINE_DIALOG(DIALOG_241, 1, 3, 30, 200, _("\
This will be our last\n\
witness!\n\
Bring him in."))
DEFINE_DIALOG(DIALOG_242, 1, 3, 30, 200, _("\
Witness number three,\n\
please introduce\n\
yourself."))
DEFINE_DIALOG(DIALOG_243, 1, 1, 30, 200, _("\
I'm Whomp."))
DEFINE_DIALOG(DIALOG_244, 1, 2, 30, 200, _("\
Okay!"))
DEFINE_DIALOG(DIALOG_245, 1, 2, 30, 200, _("\
Your honor, may I\n\
ask my first question?"))
DEFINE_DIALOG(DIALOG_246, 1, 3, 30, 200, _("\
Mr Whomp,\n\
have you ever met\n\
the defendant?"))
DEFINE_DIALOG(DIALOG_247, 1, 1, 30, 200, _("\
Yes."))
DEFINE_DIALOG(DIALOG_248, 1, 1, 30, 200, _("\
Can you elaborate?"))
DEFINE_DIALOG(DIALOG_249, 1, 1, 30, 200, _("\
Yes."))
DEFINE_DIALOG(DIALOG_250, 1, 1, 30, 200, _("\
Will you do it?"))
DEFINE_DIALOG(DIALOG_251, 1, 1, 30, 200, _("\
Yes."))
DEFINE_DIALOG(DIALOG_252, 1, 1, 30, 200, _("\
When?!"))
DEFINE_DIALOG(DIALOG_253, 1, 1, 30, 200, _("\
I don't know."))
DEFINE_DIALOG(DIALOG_254, 1, 1, 30, 200, _("\
This is rotten!"))
DEFINE_DIALOG(DIALOG_255, 1, 4, 30, 200, _("\
Defendant Wario, it seems\n\
you will have to be\n\
more specific with\n\
your questions."))
DEFINE_DIALOG(DIALOG_256, 1, 4, 30, 200, _("\
.....\n\
..........\n\
......\n\
..\n\
Alright then...\n\
Please detail everything\n\
you know about Waluigi."))
DEFINE_DIALOG(DIALOG_257, 1, 5, 30, 200, _("\
He's a lanky man.\n\
He smells really bad.\n\
He is my friend.\n\
He came to the fortress.\n\
He has a foul mouth.\n\
He is very tall.\n\
I jumped 5 feet high\n\
and crushed him.\n\
Waluigi beat the king."))
DEFINE_DIALOG(DIALOG_258, 1, 2, 30, 200, _("\
There you have it!\n\
Waluigi was the one!"))
DEFINE_DIALOG(DIALOG_259, 1, 3, 30, 200, _("\
Very convincing evidence!\n\
It seems Waluigi\n\
really was the hero.\n\
That is unless\n\
Mr Toad can punch a\n\
hole in this story!"))
DEFINE_DIALOG(DIALOG_260, 1, 5, 30, 200, _("\
This seems lost!\n\
I'm pooped.\n\
Mario, did you notice\n\
anything wrong in\n\
Mr Whomp's story?\n\
1) Whomps can't\n\
   jump 5 feet high!\n\
2) Impossible, Waluigi is\n\
   taller than 5 feet!\n\
//1)////2)"))
DEFINE_DIALOG(DIALOG_261, 1, 5, 30, 200, _("\
There is an inconsistency\n\
in that story!\n\
He claims to jump 5 feet,\n\
but Waluigi is way taller\n\
than that!\n\
My client is that short!\n\
He was talking about\n\
Mario!"))
DEFINE_DIALOG(DIALOG_262, 1, 2, 30, 200, _("\
Okay! Good catch!\n\
\n\
Mr Whomp, can you\n\
explain that?"))
DEFINE_DIALOG(DIALOG_263, 1, 1, 30, 200, _("\
No."))
DEFINE_DIALOG(DIALOG_264, 1, 4, 30, 200, _("\
... I think I'm\n\
going to have to\n\
disqualify this\n\
witness as well.\n\
I'm inclined to\n\
side with Mario."))
DEFINE_DIALOG(DIALOG_265, 1, 3, 30, 200, _("\
That is impossible,\n\
Whomps can't jump\n\
5 feet high!\n\
They are way too\n\
heavy!"))
DEFINE_DIALOG(DIALOG_266, 1, 3, 30, 200, _("\
Is that true?\n\
Mr Whomp, can you\n\
jump 5 feet high?"))
DEFINE_DIALOG(DIALOG_267, 1, 1, 30, 200, _("\
Yes."))
DEFINE_DIALOG(DIALOG_268, 1, 3, 30, 200, _("\
That's a bummer.\n\
We really messed this\n\
one up, Mario!"))
DEFINE_DIALOG(DIALOG_269, 1, 2, 30, 200, _("\
No no no!\n\
This is unfair!"))
DEFINE_DIALOG(DIALOG_270, 1, 4, 30, 200, _("\
Mr Waluigi, please\n\
stay professional.\n\
If you do not have\n\
any further witnesses,\n\
I will have to give\n\
this case to Mario."))
DEFINE_DIALOG(DIALOG_271, 1, 2, 30, 200, _("\
Great job, Mario!\n\
You could be a lawyer!\n\
I think we won this\n\
case!"))
DEFINE_DIALOG(DIALOG_272, 1, 5, 30, 200, _("\
Okay!\n\
It seems the defense\n\
has nothing else to\n\
bring to the table.\n\
\n\
It is clear that\n\
Mario is the hero.\n\
\n\
\n\
\n\
I hereby declare that\n\
Mario shall receive his\n\
copyrights back and\n\
Waluigi will pay 1 Star\n\
in reperations.\n\
Please hand it over now."))
DEFINE_DIALOG(DIALOG_273, 1, 1, 30, 200, _("\
Oh no!"))
DEFINE_DIALOG(DIALOG_274, 1, 2, 30, 200, _("\
Owch!\n\
Not fair!"))



