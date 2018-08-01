#include<vector>
#include<thread>
#include "common.h"
#include "cube.h"


using bits = uint64_t;
using all_piece_t = std::vector<bits>;
using all_piece_iter_t = all_piece_t::iterator;
using all_piece_citer_t = all_piece_t::const_iterator;
using all_piece_tracker_t = Tracker<all_piece_citer_t>;

const unsigned int __max_thread = std::thread::hardware_concurrency();//can return 0
const unsigned int max_thread = __max_thread > 1 ? __max_thread : 1;
const int start_piece = 1;
time_t start_time;
std::mutex plock;

bool doublecheck(bits const& map, all_piece_citer_t const& start, all_piece_citer_t const& end)
{
  for(auto it = start; it < end; ++it)
    if(map == *it)
      return true;
  return false;
}

size_t fill_cube_permutations(bits cube, all_piece_t& container)
{
  //the most possible permutations is 1536(64 * 24) with bitmap 0b1
  //but with filtering rotation doubles the most achievable is 576(24 * 24) with bitmap 0b10111
  size_t nr = 0;
  Cube zpiece = Cube(cube);
  do
  {
    Cube ypiece = zpiece;
    do
    {
      Cube xpiece = ypiece;
      do
      {
        Cube piece = xpiece;
        all_piece_citer_t iter_nr = container.cbegin() + nr;
        if(doublecheck(piece.get(), iter_nr, container.cend()))
          continue;
        container.insert(iter_nr, piece.get());
        ++nr;
        for(int i = 1; i < 24; ++i)
        {
          if(i % 12)
            if(i % 4)
              piece.rotatez();
            else
              piece.rotatey();
          else
            piece.rotatexx();
          container.push_back(piece.get());
        }
      }
      while(xpiece.try_shiftx());
    }
    while(ypiece.try_shifty());
  }
  while(zpiece.try_shiftz());
  container.shrink_to_fit();
  return nr;
}

void printsol(all_piece_citer_t* piece)
{
  std::cout << "solution found at ";
  get_time(std::cout, start_time) << ":\n";
  std::cout << *piece[0];
  for(int pi = 1; pi < max_piece; ++pi)
    std::cout << " " << *piece[pi];
  std::cout << std::endl;
}

void solve(all_piece_t const* all, all_piece_citer_t const& index)
{
  all_piece_citer_t piece[max_piece];
  piece[0] = index;
  for(int pi = start_piece; pi < max_piece; ++pi)
    piece[pi] = all[pi].cbegin();
  bits total = *piece[0];
  plock.lock();
  std::cout << "started with solving from piece 0 (" << total << ") at ";
  get_time(std::cout, start_time) << std::endl;
  plock.unlock();
  int pi = start_piece;
  goto start; //enter loop unconditionally
  while(pi > start_piece) //exit before going back to indexed piece
  {
    piece[pi] = all[pi].cbegin(); //return iterator to beginning
    total ^= *piece[--pi]++; //remove last piece and go to next permutation
start:
    while(piece[pi] < all[pi].cend()) //until end
    {
      if(*piece[pi] & total) //piece does not fit
        ++piece[pi]; //next permutation
      else if(pi == last_piece) //last piece fits
      {
        printsol(piece); //solution found
        ++piece[pi]; //next permutation
      }
      else //piece fits
        total |= *piece[pi++]; //add to total and increment
    }
  }
  std::cout << "finished with solving from piece 0 (" << total << ") at ";
  get_time(std::cout, start_time) << std::endl;
}

void thread(all_piece_t const* all, all_piece_tracker_t& progress)
{
  while(progress.get())
    solve(all, progress.release());
}


int main()
{
  all_piece_t all[max_piece];
  for(int pi = 0; pi < max_piece; ++pi)
    fill_cube_permutations(pieces[pi], all[pi]);
  size_t count = all[0].size() / 24;
  all_piece_citer_t end = all[0].cbegin() + count;
  size_t threads_used = max_thread <= count ? max_thread - 1 : count;
  std::thread threads[threads_used];
  all_piece_tracker_t progress(all[0].cbegin(), end);
  time(&start_time);
  for(size_t i = 0; i < threads_used; ++i)
    threads[i] = std::thread(thread, all, std::ref(progress));
  thread(all, std::ref(progress));
  for(size_t i = 0; i < threads_used; ++i)
    threads[i].join();
  std::cout << "\ndone" << std::endl;
}

