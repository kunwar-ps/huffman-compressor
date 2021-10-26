<h3> updation </h3>

<hr>

<b>in source.cpp</b><br>compressor

<ul>
  
  <li>added dfs code for tree traversal. though not used. created for better memory managment of string(huffman code string) that is to be passed on each call. not used</li>
  <li>updated read functions to read 10000 / 10000 bytes at a time. for avoiding unncessary read calls of one byte.</li>
  <li>added streamer class that throws to file a 100000 bytes string at a time and then flushes in last.</li>
  <li>added local hash map using static memory, unordered was slow.</li>

</ul>

<h3>to do-</h3>

<b>in source2.cpp</b><br>decompressor

<ul>
  <li>add trie</li>
  <li>avoid using hash maps as much</li>
  <li>hash maps are slow than local array hash</li>
</ul>

