using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lithe
{

	public class SpriteRendererComponent : Component
	{
		public Vec4 Color
		{
			get
			{
				InternalCalls.SpriteRendererComponent_GetColor(Entity.ID, out Vec4 color);
				return color;
			}
			set => InternalCalls.SpriteRendererComponent_SetColor(Entity.ID, ref value);
		}

		public bool SubtextureUsed
		{
			get => InternalCalls.SpriteRendererComponent_SubtextureUsed(Entity.ID);
			set
			{
				if (value)
					InternalCalls.SpriteRendererComponent_EnableSubtexture(Entity.ID);
				else
					InternalCalls.SpriteRendererComponent_DisableSubtexture(Entity.ID);
			}
		}

		public Vec2 Coords
		{
			get
			{
				InternalCalls.SpriteRendererComponent_GetCoords(Entity.ID, out Vec2 coords);
				return coords;
			}
			set => InternalCalls.SpriteRendererComponent_SetCoords(Entity.ID, ref value);
		}

		public Vec2 CellSize
		{
			get
			{
				InternalCalls.SpriteRendererComponent_GetCellSize(Entity.ID, out Vec2 cellSize);
				return cellSize;
			}
			set => InternalCalls.SpriteRendererComponent_SetCellSize(Entity.ID, ref value);
		}

		public Vec2 SpriteSize
		{
			get
			{
				InternalCalls.SpriteRendererComponent_GetSpriteSize(Entity.ID, out Vec2 spriteSize);
				return spriteSize;
			}
			set => InternalCalls.SpriteRendererComponent_SetSpriteSize(Entity.ID, ref value);
		}

		public string TextureAbsolutePath => InternalCalls.SpriteRendererComponent_GetTextureAbsolutePath(Entity.ID);

		public string TextureRelativePath => InternalCalls.SpriteRendererComponent_GetTextureRelativePath(Entity.ID);

		public bool IsLoaded => InternalCalls.SpriteRendererComponent_IsLoaded(Entity.ID);

		public void SetTexture(string relativePath)
		{
			InternalCalls.SpriteRendererComponent_SetTexturePath(Entity.ID, relativePath);
		}
	}

	public class CircleRendererComponent : Component
	{
		public Vec4 Color
		{
			get
			{
				InternalCalls.CircleRendererComponent_GetColor(Entity.ID, out Vec4 color);
				return color;
			}
			set
			{
				InternalCalls.CircleRendererComponent_SetColor(Entity.ID, ref value);
			}
		}

		public float Radius
		{
			get => InternalCalls.CircleRendererComponent_GetRadius(Entity.ID);
			set => InternalCalls.CircleRendererComponent_SetRadius(Entity.ID, value);
		}

		public float Thickness
		{
			get => InternalCalls.CircleRendererComponent_GetThickness(Entity.ID);
			set => InternalCalls.CircleRendererComponent_SetThickness(Entity.ID, value);
		}

		public float Fade
		{
			get => InternalCalls.CircleRendererComponent_GetFade(Entity.ID);
			set => InternalCalls.CircleRendererComponent_SetFade(Entity.ID, value);
		}
	}

}
