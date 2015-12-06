# Generates a title based on the current directory tree
# e.g. foo-bar/qux/index.html -> Foo Bar - Qux
def sitemap_page_title
  # Grab the destination path from the current_page data
  dest_path = current_page.destination_path
  # Replace all dashes with spaces
  # (i.e. getting-started -> getting started)
  dest_path = dest_path.gsub('-', ' ')
  # Replace all '/' with dashes and slice the last-most file
  # (i.e. getting started/foo/index.html -> getting started - foo)
  dest_path = dest_path.split('/')[0...-1].join(' - ')
  # Capitalize every word
  page_title = dest_path.split.map(&:capitalize).join(' ')
  # Return nil if no page title, or the page_title
  page_title.strip.length > 0 ? page_title : nil
end