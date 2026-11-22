# Notes from watching the [video](https://youtu.be/bwBrduQ1RUE)

- `external` folder - include header files are what the user of the library would import to run map-reduce
  - they would implement the base classes and register_tasks_and_check function header defined there
  - MapReduce class sets up the job
- `test` folder - example of how user would call the job
  - main function creates the MapReduce class
  - config.ini - parameters for the MapReduce class like how to shard, ips of workers, etc.
- `src` <-- ONLY place you would touch, about 5 files total
  - `mapreduce_impl.cc` actually calls the set up of master / worker threads + sharding, but it's a bit simpler compared to the og google paper - you don't actually touch this
  - sharding function is in `file_shard.h` TOUCH, see description.md for more details
  - `mapreduce_spec.h` TOUCH - read and create struct for config.ini - holds everything that master would need
    - validate function is separate from read, but just makes sure that the config provided isn't weird, file exists, etc.
  - worker has a main function in `run_worker.cc` (don't touch), and is started via ./worker host:port
  - `worker.h` TOUCH - implement some way for worker to pull task from master, or receive task from master
    - functions are referenced via na "id" so `get_mapper_from_task_factory("id")` returns a MappingClass with `map` method and `get_reducer_from_task_factory("id")` returns a ReducerClass with `reduce` method
      - worker is a "friend" of Mapper/Reducer tasks so it has access to private
  - `mr_tasks.h` TOUCH - `emit` methods for both mapper and reducer classes - meant to write intermediate results to some file
  - `master.h` TOUCH
    - constructor just takes in the config (where most args are) and a list of shards
    - in charge of assigning tasks to workers via `masterworker.proto` TOUCH
    - also in charge of retry logic

Note, RPC is only needed to send out and monitor tasks. For final collection of reduce results, you can just directly read the files since we don't actually have a DFS.

To run the code:
```sh
cd src
make
cd -
```
should produce `libmapreduce.a` and `libmr_worker.a`.

Then do:
```sh
cd test
make
```
which would produce `mrdemo` (main thread + master binary) and `mr_worker` (worker binary)

Then make sure to start all of the workers:
```sh
./mr_worker localhost:50051 &
./mr_worker localhost:50052 &
```
then the master:
```sh
./mrdemo config.ini
```
Results should appear in `output` dir. Check there for the correct results

Don't forget to kill all of your workers after done!