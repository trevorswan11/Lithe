using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lithe
{

	public class RelationshipComponent : Component
	{
		public ulong Parent
		{
			get => InternalCalls.RelationshipComponent_GetParent(Entity.ID);
			set => InternalCalls.RelationshipComponent_SetParent(Entity.ID, value);
		}

		public ulong FirstChild
		{
			get => InternalCalls.RelationshipComponent_GetFirstChild(Entity.ID);
			set => InternalCalls.RelationshipComponent_SetFirstChild(Entity.ID, value);
		}

		public ulong NextSibling
		{
			get => InternalCalls.RelationshipComponent_GetNextSibling(Entity.ID);
			set => InternalCalls.RelationshipComponent_SetNextSibling(Entity.ID, value);
		}

		public ulong PreviousSibling
		{
			get => InternalCalls.RelationshipComponent_GetPreviousSibling(Entity.ID);
			set => InternalCalls.RelationshipComponent_SetPreviousSibling(Entity.ID, value);
		}
	}

}
