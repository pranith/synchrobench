.PHONY:	all

BENCHS = src/trees/sftree src/linkedlists/lockfree-list src/hashtables/lockfree-ht src/trees/rbtree
LBENCHS = src/trees/tree-lock src/linkedlists/lock-coupling-list src/linkedlists/lazy-list src/hashtables/lockbased-ht 
LFBENCHS = src/trees/lfbstree src/linkedlists/lockfree-list src/hashtables/lockfree-ht

#MAKEFLAGS+=-j4

MALLOC=TC

.PHONY:	clean all $(BENCHS) $(LBENCHS)

all:	lock spinlock lockfree estm sequential

lock: clean-build
	$(MAKE) "LOCK=MUTEX" $(LBENCHS)

spinlock: clean-build
	$(MAKE) "LOCK=SPIN" $(LBENCHS)

sequential: clean-build
	$(MAKE) "STM=SEQUENTIAL" $(BENCHS)

lockfree: clean-build
	for dir in $(LFBENCHS); do \
	$(MAKE) "STM=LOCKFREE" -C $$dir; \
	done

estm: clean-build
	$(MAKE) -C src/utils/estm-0.3.0
	$(MAKE) "STM=ESTM" $(BENCHS)

clean-build: 
	rm -rf build

clean:
	$(MAKE) -C src/utils/estm-0.3.0 clean
	$(MAKE) -C src/utils/estm-0.2.4.3 clean
	rm -rf build bin

$(BENCHS):
	$(MAKE) -C $@ $(TARGET)

$(LBENCHS):
	$(MAKE) -C $@ $(TARGET)
