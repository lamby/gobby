/* gobby - A GTKmm driven libobby client
 * Copyright (C) 2005, 2006 0x539 dev group
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _GOBBY_PREFERENCES_HPP_
#define _GOBBY_PREFERENCES_HPP_

#include <gtkmm/toolbar.h>
#include "config.hpp"

#include "sourceview/sourcelanguage.hpp"
#include "sourceview/sourcelanguagesmanager.hpp"

namespace Gobby
{

class Preferences
{
public:
	typedef Glib::RefPtr<Gtk::SourceLanguage> Language;
	typedef Glib::RefPtr<Gtk::SourceLanguagesManager> LangManager;

	/** Uninitialised preferences.
	 */
	Preferences();

	/** Reads preferences values out of a config, using default values
	 * for values that do not exist in the config.
	 */
	Preferences(Config& m_config, const LangManager& lang_mgr);

	/** Serialises preferences back to config.
	 */
	void serialise(Config& config) const;

	class Editor
	{
	public:
		Editor();
		Editor(Config::ParentEntry& entry);
		void serialise(Config::ParentEntry& entry) const;

		unsigned int tab_width;
		bool tab_spaces;
		bool indentation_auto;
		bool homeend_smart;
	};

	class View
	{
	public:
		View();
		View(Config::ParentEntry& entry);
		void serialise(Config::ParentEntry& entry) const;

		bool wrap_text;
		bool wrap_words;
		bool linenum_display;
		bool curline_highlight;
		bool margin_display;
		unsigned int margin_pos;
		bool bracket_highlight;
	};

	class Appearance
	{
	public:
		Appearance();
		Appearance(Config::ParentEntry& entry);
		void serialise(Config::ParentEntry& entry) const;

		Gtk::ToolbarStyle toolbar_show;
		bool remember;
	};

	class Font
	{
	public:
		Font();
		Font(Config::ParentEntry& entry);
		void serialise(Config::ParentEntry& entry) const;

		Pango::FontDescription desc;
	};

	class FileList
	{
	public:
		typedef std::map<Glib::ustring, Language> map_type;

		class iterator
		{
		private:
			typedef map_type::const_iterator base_iterator;

		public:
			iterator(base_iterator iter);

			iterator& operator++();
			iterator operator++(int);

			bool operator==(const iterator& other) const;
			bool operator!=(const iterator& other) const;

			const Glib::ustring& pattern() const;
			const Language& language() const;
		private:
			base_iterator m_iter;
		};

		FileList();
		FileList(Config::ParentEntry& entry,
		         const LangManager& lang_mgr);

		void serialise(Config::ParentEntry& entry) const;

		// This function may also return an already existing iterator
		// when pattern is already in the map. Compare lang to be sure
		// that the entry actually has been inserted.
		iterator add(const Glib::ustring& pattern,
		             const Language& lang);

		iterator begin() const;
		iterator end() const;
	protected:
		iterator add_by_mime_type(const Glib::ustring& pattern,
		                          const Glib::ustring& mime_type,
		                          const LangManager& lang_mgr);

		map_type m_files;
	};

	Editor editor;
	View view;
	Appearance appearance;
	Font font;
	FileList files;
};

}

#endif // _GOBBY_PREFERENCES_HPP_

