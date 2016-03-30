package cs12.list;

public class LinkedList {
	private class Node {
		Student data;
		Node next;
		Node prev;

		public Node(Student data){
			this.data = data;
			this.next = null;
			this.prev = null;
		}
	}

	private Node head = null;
	private Node tail = null;
	private int size = 0;

	private Node atIndex(int index) {
		if(index < 0 || index >= size) return null;
		int smi = size - index;
		smi--;
		Node ptr = head;
		if(smi < index) {
			ptr = tail;
			while(smi > 0){
				ptr = ptr.prev;
				smi--;
			}
		} else {
			while(index > 0) {
				ptr = ptr.next;
				index--;
			}
		}
		return ptr;
	}

	public String toString() {
		String output = "";
		Node ptr = head;
		output += "size: " + this.size + "\n\n";
		for(int x = 0; x < this.size; x++){
			output += ptr.data;
			ptr = ptr.next;
		}
		return output;
	}

	public String toStringRaw() {
		String output = "";
		Node ptr = head;
		while(ptr != null) {
			output += ptr.data.toStringRaw();
			ptr = ptr.next;
		}
		return output;
	}

	public void add(Student data, int index) {
		if(index < 0 || index > size) return;
		Node newnode = new Node(data);
		//could still be refactored
		if(size == 0){
			//System.out.println("new");
			head = newnode;
			tail = newnode;
		} else if(index == size) { //tail
			//System.out.println("tail");
			//Node newnode = new Node(data);
			newnode.prev = tail;
			tail.next = newnode;
			tail = newnode;
		} else if(index == 0) { //head
			//System.out.println("head");
			//Node newnode = new Node(data);
			newnode.next = head;
			head.prev = newnode;
			head = newnode;
		} else {
			//middle
			//System.out.println("mid");
			//Node newnode = new Node(data);
			Node ptr = atIndex(index);
			newnode.prev = ptr.prev;
			ptr.prev.next = newnode;
			newnode.next = ptr;
			ptr.prev = newnode;
		}

		size++;
		return;
	}

	public Student remove(int index) {
		if(index < 0 || index >= size) return null;
		Node ptr = atIndex(index);

		if(index == 0) { //head
			head = ptr.next;
		} else if(index == size-1) { //tail
			tail = ptr.prev;
		}

		//middle
		if(ptr.prev != null) ptr.prev.next = ptr.next;
		if(ptr.next != null) ptr.next.prev = ptr.prev;
		size--;
		return ptr.data;
	}

	public void qsort() {
		if(size < 2) return;
		qsort_rec(0, size);
	}

	private void qsort_rec(int start, int end) { //[start, end)
		if(end - start <= 1) return;
		System.out.println(this);
		Node pivot = atIndex(start);
		Node leftm = atIndex(start);
		Node rghtm = atIndex(end-1);
		Student tmp = null;
		int lndx = start;
		int rndx = end-1;
		Boolean hasLooped = false;
		System.out.println("" + start + " " + end);
		System.out.println("pivot: " + pivot.data + ", leftm: " + leftm.data + ", rghtm: " + rghtm.data);
		if(end - start == 2) {
			if(leftm.data.getName().compareTo(rghtm.data.getName()) > 0) {
				System.out.println("swap1 "+leftm.data+" and "+rghtm.data);
				tmp = leftm.data;
				leftm.data = rghtm.data;
				rghtm.data = tmp;
			}
			return;
		}
		while(leftm.prev != rghtm && leftm != rghtm) {
			if(lndx != start) {
				//swap
				System.out.println("swap2 "+leftm.data+" and "+rghtm.data);
				tmp = leftm.data;
				leftm.data = rghtm.data;
				rghtm.data = tmp;
			}
			while(leftm.data.getName().compareTo(pivot.data.getName()) <= 0 && leftm.next != null){
				System.out.println("movel");
				leftm = leftm.next;
				lndx++;
			}
			while(rghtm.data.getName().compareTo(pivot.data.getName()) > 0 && rghtm.prev != null){
				System.out.println("mover");
				rghtm = rghtm.prev;
				rndx--;
			}
		}
		//swap pivot
		tmp = pivot.data;
		pivot.data = rghtm.data;
		rghtm.data = tmp;
		qsort_rec(start, rndx+1);
		qsort_rec(rndx+1, end);
	}

	public void clear() {
		this.head = null;
		this.tail = null;
		this.size = 0;
	}

	public LinkedList addAll(LinkedList list) {
		if(this.size == 0) {
			for(Node ptr = list.head; ptr != null; ptr = ptr.next) {
				this.add(ptr.data, this.size);
				this.size++;
			}
			return list;
		}
		this.tail.next = list.head;
		list.head.prev = this.tail;
		this.tail = list.tail;
		this.size += list.size;
		return this;
	}

	public LinkedList[] split(int index) {
		if(index < 0 || index >= this.size) return null;
		LinkedList[] output = new LinkedList[2];
		output[0] = new LinkedList();
		output[1] = new LinkedList();
		if(index == 0) {
			output[1] = this;
			return output;
		} else if(index == size-1) {
			output[0] = this;
			return output;
		}
		output[0].head = this.head;
		output[1].head = this.atIndex(index);
		output[0].tail = output[1].head.prev;
		output[1].tail = this.tail;
		output[0].size = index;
		output[1].size = this.size - index;
		return output;
	}
}
