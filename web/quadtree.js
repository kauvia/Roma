class Quadtree {
	constructor(bounds, maxDepth, maxChildren) {
		this.root = new Node(bounds, 0, maxDepth, maxChildren);
	}
	insert(item) {
		this.root.insert(item);
	}
	clear() {
		this.root.clear();
	}
	retrieve(item) {
		let retrievedItem = this.root.retrieve(item).slice(0);
		return retrievedItem;
	}
}

class Node {
	constructor(bounds, depth, maxDepth, maxChildren) {
		this.bounds = bounds;
		this.depth = depth;
		this.maxDepth = maxDepth;
		this.maxChildren = maxChildren;

        //test
        this.color = ranN(255);
        //test

		this.children = [];
		this.nodes = [];
		this.stuckChildren = [];
		this.out = [];

		this.TOP_LEFT = 0;
		this.TOP_RIGHT = 1;
		this.BOT_LEFT = 2;
		this.BOT_RIGHT = 3;
	}
	insert(item) {
		if (this.nodes.length) {
			// add into subnodes if present
			let idx = this.findIdx(item);
			let node = this.nodes[idx];
			if (
				item.x >= node.bounds.x &&
				item.x + item.width <= node.bounds.x + node.bounds.width &&
				item.y >= node.bounds.y &&
				item.y + item.height <= node.bounds.x + node.bounds.height
			) {
				this.nodes[idx].insert(item);
			} else {
				this.stuckChildren.push(item);
			}
			return;
		}
		this.children.push(item); //otherwise, push into this node

		let length = this.children.length; //check if crowded and above maxdepth
		if (!(this.depth >= this.maxDepth) && length > this.maxChildren) {
			this.subdivide(); //divde em up

			for (let i = length - 1; i >= 0; i--) {
				this.insert(this.children[i]); //put into the divided subnodes
			}
			this.children.length = 0; //empty da children
		}
	}

	getChildren() {
		return this.children.concat(this.stuckChildren);
	}

	retrieve(item) {
		let out = this.out;
		out.length = 0;
		if (this.nodes.length) {
			let idx = this.findIdx(item);
			let node = this.nodes[idx];
			if (
				item.x >= node.bounds.x &&
				item.x + item.width <= node.bounds.x + node.bounds.width &&
				item.y >= node.bounds.y &&
				item.y + item.height <= node.bounds.x + node.bounds.height
			) {
				out.push.apply(out, this.nodes[idx].retrieve(item));
			} else {
				if (item.x <= this.nodes[this.TOP_RIGHT].bounds.x) {
					if (item.y <= this.nodes[this.BOT_LEFT].bounds.y) {
						out.push.apply(out, this.nodes[this.TOP_LEFT].getAllContent());
					}
					if (item.y + item.height > this.nodes[this.BOT_LEFT].bounds.y) {
						out.push.apply(out, this.nodes[this.BOT_LEFT].getAllContent());
					}
				}
				if (item.x + item.width > this.nodes[this.TOP_RIGHT].bounds.x) {
					if (item.y <= this.nodes[this.BOT_RIGHT].bounds.y) {
						out.push.apply(out, this.nodes[this.TOP_RIGHT].getAllContent());
					}
					if (item.y + item.height > this.nodes[this.BOT_RIGHT].bounds.y) {
						out.push.apply(out, this.nodes[this.BOT_RIGHT].getAllContent());
					}
				}
			}
		}
		out.push.apply(out, this.stuckChildren);
		out.push.apply(out, this.children);
		return out;
	}

	getAllContent() {
		let out = this.out;
		if (this.nodes.length) {
			for (let i = 0; i < this.nodes.length; i++) {
				this.nodes[i].getAllContent();
			}
		}
		out.push.apply(out, this.stuckChildren);
		out.push.apply(out, this.children);
		return out;
	}

	findIdx(item) {
		let b = this.bounds;
		//add item width , height???
		let left = item.x > b.x + b.width / 2 ? false : true;
		let top = item.y > b.y + b.height / 2 ? false : true;

		let idx = this.TOP_LEFT;
		if (left) {
			if (!top) {
				idx = this.BOT_LEFT;
			}
		} else {
			top ? (idx = this.TOP_RIGHT) : (idx = this.BOT_RIGHT);
		}
		return idx;
	}

	subdivide() {
		let depth = this.depth + 1;
		let bx = this.bounds.x;
		let by = this.bounds.y;
		let bw = this.bounds.width;
		let bh = this.bounds.height;

		// top left
		this.nodes[this.TOP_LEFT] = new Node(
			{
				x: bx,
				y: by,
				width: bw / 2,
				height: bh / 2
			},
			depth,
			this.maxDepth,
			this.maxChildren
		);
		// top right
		this.nodes[this.TOP_RIGHT] = new Node(
			{
				x: bx + bw / 2,
				y: by,
				width: bw / 2,
				height: bh / 2
			},
			depth,
			this.maxDepth,
			this.maxChildren
		);
		//bot left
		this.nodes[this.BOT_LEFT] = new Node(
			{
				x: bx,
				y: by + bh / 2,
				width: bw / 2,
				height: bh / 2
			},
			depth,
			this.maxDepth,
			this.maxChildren
		);
		//bot right
		this.nodes[this.BOT_RIGHT] = new Node(
			{
				x: bx + bw / 2,
				y: by + bh / 2,
				width: bw / 2,
				height: bh / 2
			},
			depth,
			this.maxDepth,
			this.maxChildren
		);
	}
	clear() {
		this.children.length = 0;
		this.stuckChildren.length = 0;
		let length = this.nodes.length;
		if (!length) {
			return;
		}
		for (let i = 0; i < length; i++) {
			this.nodes[i].clear();
		}
		this.nodes.length = 0;
	}
}

export default Quadtree;

const ranN = num => Math.floor(Math.random() * num); //return random number from 0-num
