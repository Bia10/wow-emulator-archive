using System;
using Server.Items;
using System.Collections;
using Server;


////////////////////// Scarlet.cs
namespace Server.Creatures
{
	public class Adam: BaseCreature
	{
		public Adam() : base()
		{
			Name = "Adam";
			Id = 1366;
			Model = 338;
			Level = RandomLevel(1,1);
			SetDamage(1f+1.8f*Level,1f+2.66*Level);			
			AttackSpeed = 2000;
			Armor = 0;
			Block = 0;
			Flags1=0x08006E;
			ResistArcane = 0;
			ResistFire = 0;
			ResistFrost = 0;
			ResistHoly = 0;
			ResistNature = 0;
			ResistShadow = 0;
			 Str = 0;
			 BaseHitPoints = 60;
 			BaseMana = 0;
			BoundingRadius = 1.077550f;
			CombatReach = 0.400f;
			Speed = 3.5f;
			WalkSpeed = 3.5f;
			RunSpeed = 6.5f;
			Faction = Factions.Alliance; 
			Equip( new Item( 7453, InventoryTypes.OneHand, 4, 2, 13, 3, 0, 0, 0 ) );		
			AIEngine = new DefensiveAnimalAI( this );
			NpcType = 7;
			Unk3=1;
		}
	}
}
