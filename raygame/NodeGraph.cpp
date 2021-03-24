#include "NodeGraph.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	//Create a node pointer that points to the start node
	Node* start = start;
	//Create a node pointer that points to the goal node
	Node* goal = end;

	//Check if the start or the goal pointer is null
	if (!start || !goal)
	{
		//return an empty list
		return;
		//end if statement
	}
	//Create the deque that will hold the final path
	std::deque<Node*> path;

	//Create a node pointer that will be act as an iterator for the graph
	Node* iterator = nullptr;

	//Create an open list
	std::deque<Node*> openList;
	//Create a closed list
	std::deque<Node*> closedList;

	//Add start to the open list
	openList.push_front(start);

	//Loop while the open list is not empty
	while (openList.size() > 0)
	{
		//Sort the items in the open list by the g score
		for (int i = 0; i < openList.size(); i++)
		{
			for (int j = openList.size(); j > i; j--)
			{
				if (openList[i]->gScore > openList[j - 1]->gScore)
				{
					Node* temp = openList[i];
					openList[i] = openList[j - 1];
					openList[j - 1] = temp;
				}
			}
		}

		//Set the iterator to be the first item in the open list
		iterator = openList[0];

		//Check if the iterator is pointing to the goal node
		if (iterator == goal)
		{
			//Return the new path found
			break;
			//end if statement
		}

		//Pop the first item off the open list
		openList.pop_front();

		//Add the first item to the closed list
		closedList.push_front(iterator);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < iterator->connections.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* nodeEdgeEnd = nullptr;

			//Check if the iterator is on the second end of the node
			if (iterator == iterator->connections[i].target)
			{
				//Set the edge end pointer to be the first end of the node
				nodeEdgeEnd = iterator;
			}
			//Otherwise if the iterator is on the first end of the node...
			else
			{
				//set the edge end pointer to be the second end of the node
				nodeEdgeEnd = iterator->connections[i].target;
				// end if statement
			}

			//Check if node at the end of the edge is in the closed list
			if (!inList(closedList, nodeEdgeEnd))
			{
				//Create an int and set it to be the g score of the iterator plus the cost of the edge
				int costOf = iterator->gScore + iterator->connections[i].cost;

				//Check if the node at the end of the edge is in the open list
				if (!inList(openList, nodeEdgeEnd))
				{
					//Set the nodes g score to be the g score calculated earlier
					nodeEdgeEnd->gScore = costOf;

					//Set the nodes previous to be the iterator
					nodeEdgeEnd->previous = iterator;

					//Add the node to the open list
					openList.push_front(nodeEdgeEnd);
				}
				//Otherwise if the g score is less than the node at the end of the edge's g score...
				else if (costOf < nodeEdgeEnd->gScore)
				{
					//Set its g score to be the g score calculated earlier
					nodeEdgeEnd->gScore = costOf;

					//Set its previous to be the current node
					nodeEdgeEnd->previous = iterator;
				}
			}
			//end if statement
		}
		//end loop
	}
	//end loop

	//The iterator is currently pointing to the goal node
	//	loop while the iterator is not null
	while (iterator)
	{
		//Adds a node to the front of the path list
		path.push_front(iterator);
		//iterate to the previous node
		iterator = iterator->previous;
	}
	//Returns the path that gets to the goal with the cheapest gScore
	return path;
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}

bool NodeGraph::inList(std::deque<Node*> list, Node* node)
{
	//iterates through entire deque List
	for (int i = 0; i < list.size(); i++)
		//Checks to see if the node at the current iteration is the desired node
		if (list[i] == node)
		{
			//If this is the node, return true
			return true;
		}
	//If the function made it this far, the node was not in the list
	return false;
}
