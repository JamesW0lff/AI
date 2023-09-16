#pragma once

namespace AI
{
	class GridBasedGraph
	{
		public:
			#pragma region STRUCT NODE
			struct Node
			{
				// Graph connection data
				std::array<Node*, 8> neighbours;
				int column = 0;
				int row = 0;

				// Search data
				Node* parent = nullptr;
				float g = 0.0f;
				float h = 0.0f;
				bool opened = false; 
				bool closed = false;
			};
			#pragma endregion

			void Initialize(int columns, int rows);
			void ResetSearchParams();

			#pragma region GET NODE
			Node* GetNode(int column, int row)
			{
				// Bound checking
				// If it is out of bound, then return nullptr
				if (column < 0 || column >= mColumns ||
					row < 0 || row >= mRows)
				{
					return nullptr;
				}

				return &mNodes[column + (row * mColumns)];
			}
			#pragma endregion

			#pragma region CONST GET NODE
			const Node* GetNode(int column, int row) const
			{
				if (column < 0 || column >= mColumns ||
					row < 0 || row >= mRows)
				{
					return nullptr;
				}

				return &mNodes[column + (row * mColumns)];
			}
			#pragma endregion

			int GetColumns() const { return mColumns; }
			int GetRows() const { return mRows; }

		private:
			std::vector<Node> mNodes;
			int mColumns = 0;
			int mRows = 0;
	};
}